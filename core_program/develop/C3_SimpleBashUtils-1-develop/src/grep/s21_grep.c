#include "s21_grep.h"

#include "../common/s21_common.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    arguments arg = {false};
    parse(&arg, argc, argv);
    if (!arg.error && arg.pattern) output(arg, argc, (const char *const *)argv);
    free(arg.pattern);
  } else
    fprintf(stderr,
            "Usage: %s [OPTION]... PATTERNS [FILE]...\nTry 'grep "
            "--help' for more information.\n",
            argv[0]);
  return 0;
}

void parse(arguments *arg, int argc, char *const argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg->e = true;
        if ((arg->error = find_unmatched_regexec(optarg)) == -1)
          fprintf(stderr, "%s: Invalid regular expression\n", argv[0]);
        else if ((arg->error = find_unmatched_regexec(optarg)) == -2)
          fprintf(stderr, "%s: Trailing backslash\n", argv[0]);
        else if (add_pattern(arg, argv[0], optarg))
          return;
        break;
      case 'i':
        arg->i = REG_ICASE;
        break;
      case 'v':
        arg->v = true;
        break;
      case 'c':
        arg->c = true;
        break;
      case 'l':
        arg->l = true;
        break;
      case 'n':
        arg->n = true;
        break;
      case 'h':
        arg->h = true;
        break;
      case 's':
        arg->s = true;
        break;
      case 'f':
        arg->f = true;
        if (obtain_patterns_from_file(arg, argv[0], optarg)) arg->error = true;
        break;
      case 'o':
        arg->o = true;
        break;
      default:
        arg->error = true;
        fprintf(stderr,
                "Usage: %s [OPTION]... PATTERNS [FILE]...\nTry 'grep "
                "--help' for more information.\n",
                argv[0]);
    }
  }
  if_no_flags(arg, argc, argv);
}

void output(arguments arg, int argc, const char *const argv[]) {
  if (arg.o && !arg.l && !arg.c)
    if (find_mnemonic_symbols(arg.pattern)) return;
  regex_t regex;
  int error = regcomp(&regex, arg.pattern, REG_NEWLINE | arg.i);
  if (error) {
    fprintf(stderr, "%s: Regex compilation error\n", argv[0]);
    return;
  }
  for (int i = optind; i < argc; ++i) {
    int flag = 1;
    if (!arg.s) flag = file_check(argv[0], argv[i]);
    if (flag != -1) read_from_file(arg, argv[0], argv[i], &regex);
  }
  regfree(&regex);
}

void read_from_file(arguments arg, const char *cmd, const char *filepath,
                    regex_t *regex) {
  FILE *file = fopen(filepath, "r");
  if (!file) return;
  char *line = NULL;
  size_t line_size = 0, line_number = 0, matched_lines = 0;
  int length = get_line(&line, &line_size, file);
  while (length > 0) {
    ++line_number;
    int result = regexec(regex, line, 0, NULL, 0);
    if ((!result && !arg.v) || (result && arg.v && !arg.o)) {
      if (!arg.c && !arg.l) {
        if (!arg.h && !arg.o) printf("%s:", filepath);
        if (arg.n && !arg.o) printf("%zu:", line_number);
        if (arg.o) {
          if (line[length - 1] == '\n') line[length - 1] = '\0';
          output_matches(arg, regex, filepath, line, line_number);
        } else
          output_line(line, length);
      }
      ++matched_lines;
    } else if (!result && arg.v && arg.o)
      ++matched_lines;
    length = get_line(&line, &line_size, file);
  }
  free(line);
  line = NULL;
  if (arg.l && matched_lines) {
    if (matched_lines == line_number && arg.v && arg.o) {
      fclose(file);
      return;
    }
    printf("%s\n", filepath);
  } else if (arg.l && !matched_lines && arg.v && arg.o && line_number)
    printf("%s\n", filepath);
  else if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", filepath);
    if (arg.v && arg.o)
      printf("%zu\n", line_number - matched_lines);
    else
      printf("%zu\n", matched_lines);
  }
  fclose(file);
  if (length == -2) fprintf(stderr, "%s: Memory allocation error\n", cmd);
}