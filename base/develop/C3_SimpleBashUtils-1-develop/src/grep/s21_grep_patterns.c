#include "s21_grep.h"

int add_pattern(arguments *arg, const char *cmd, const char *pattern) {
  size_t length = strlen(pattern);
  if (arg->pattern == NULL) {
    arg->pattern_memory = 10;
    char *tmp = (char *)malloc(arg->pattern_memory);
    if (tmp == NULL) {
      fprintf(stderr, "%s: Memory allocation error\n", cmd);
      return 1;
    }
    arg->pattern = tmp;
  }
  if (arg->pattern_memory < arg->pattern_length + length + 7) {
    arg->pattern_memory = (arg->pattern_length + length + 7) * 2;
    char *tmp = (char *)realloc(arg->pattern, arg->pattern_memory);
    if (tmp == NULL) {
      fprintf(stderr, "%s: Memory allocation error\n", cmd);
      arg->pattern = NULL;
      return 1;
    }
    arg->pattern = tmp;
  }
  if (arg->pattern_length != 0) {
    strcat(arg->pattern + arg->pattern_length, "\\|");
    arg->pattern_length += 2;
  }
  arg->pattern_length +=
      sprintf(arg->pattern + arg->pattern_length, "\\(%s\\)", pattern);
  return 0;
}

int obtain_patterns_from_file(arguments *arg, const char *cmd,
                              const char *filepath) {
  if (file_check(cmd, filepath) != 1) return 1;
  FILE *file = fopen(filepath, "r");
  char *line = NULL;
  size_t line_size = 0, line_number = 0;
  size_t error_count = 0;
  int length = get_line(&line, &line_size, file);
  while (length > 0) {
    ++line_number;
    if (find_unmatched_regexec(line) == -1) {
      fprintf(stderr, "%s: %s:%zu: Invalid regular expression\n", cmd, filepath,
              line_number);
      ++error_count;
    } else if (find_unmatched_regexec(line) == -2) {
      fprintf(stderr, "%s: %s:%zu: Trailing backslash\n", cmd, filepath,
              line_number);
      ++error_count;
    }
    length = get_line(&line, &line_size, file);
  }
  if (error_count) return 1;
  fseek(file, 0, SEEK_SET);
  length = get_line(&line, &line_size, file);
  line_number = 0;
  while (length > 0) {
    ++line_number;
    if (line[length - 1] == '\n' && strlen(line) > 1) line[length - 1] = '\0';
    if (add_pattern(arg, cmd, line)) {
      fclose(file);
      return 1;
    }
    length = get_line(&line, &line_size, file);
  }
  free(line);
  line = NULL;
  fclose(file);
  if (length == -2) {
    fprintf(stderr, "%s: Memory allocation error\n", cmd);
    return 1;
  }
  return 0;
}

int find_unmatched_regexec(const char *pattern) {
  int flag = 0;
  for (int i = 0; pattern[i] != '\0' && !flag; ++i) {
    if (pattern[i] == '[' && pattern[i + 1] == ']') {
      for (int j = i + 2; pattern[j] != '\0'; ++j)
        if (pattern[j] == ']') return flag;
      flag = -1;
    } else if (pattern[i] == '[' && pattern[i + 1] == '^' &&
               pattern[i + 2] == ']') {
      for (int j = i + 3; pattern[j] != '\0'; ++j)
        if (pattern[j] == ']') return flag;
      flag = -1;
    } else if (pattern[i] == '[') {
      for (int j = i + 1; pattern[j] != '\0'; ++j)
        if (pattern[j] == ']') return flag;
      flag = -1;
    }
  }
  for (int i = 0; pattern[i] != '\0' && !flag; ++i) {
    if ((pattern[i] == '\\' && pattern[i + 1] != '\0' &&
         pattern[i + 1] != '\n'))
      ++i;
    else if ((pattern[i] == '\\' && pattern[i + 1] == '\0') ||
             (pattern[i] == '\\' && pattern[i + 1] == '\n'))
      flag = -2;
  }
  return flag;
}

void if_no_flags(arguments *arg, int argc, char *const argv[]) {
  if (!arg->f && !arg->pattern) {
    if (find_unmatched_regexec(argv[optind]) == -1) {
      fprintf(stderr, "%s: Invalid regular expression\n", argv[0]);
      arg->error = true;
    } else if (find_unmatched_regexec(argv[optind]) == -2) {
      fprintf(stderr, "%s: Trailing backslash\n", argv[0]);
      arg->error = true;
    } else if (add_pattern(arg, argv[0], argv[optind]))
      return;
    ++optind;
  }
  if (argc - optind == 1) arg->h = true;
}

int find_mnemonic_symbols(const char *pattern) {
  const char *patterns_to_remove[] = {"\\(^\\)\\|", "\\($\\)\\|", "\\|\\(^\\)",
                                      "\\|\\($\\)"};
  for (int i = 0; i < 4; i++) {
    char *str;
    while ((str = strstr(pattern, patterns_to_remove[i]))) {
      memmove(str, str + strlen(patterns_to_remove[i]),
              strlen(str + strlen(patterns_to_remove[i])) + 1);
      if (!strcmp(pattern, "\\(^\\)") || !strcmp(pattern, "\\($\\)")) return 1;
    }
  }
  return (!strcmp(pattern, "\\(^\\)") || !strcmp(pattern, "\\($\\)")) ? 1 : 0;
}