#include "s21_cat.h"

#include "../common/s21_common.h"

int main(int argc, char *argv[]) {
  flags arg = parse(argc, argv);
  if (!arg.error) output(arg, argc, (const char *const *)argv);
  return 0;
}

flags parse(int argc, char *const argv[]) {
  flags arg = {false};
  const struct option long_flags[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {0, 0, 0, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, "bevEnstT", long_flags, NULL)) != -1) {
    switch (opt) {
      case 'b':
        arg.b = true;
        break;
      case 'e':
        arg.E = true;
        arg.v = true;
        break;
      case 'v':
        arg.v = true;
        break;
      case 'E':
        arg.E = true;
        break;
      case 'n':
        arg.n = true;
        break;
      case 's':
        arg.s = true;
        break;
      case 't':
        arg.T = true;
        arg.v = true;
        break;
      case 'T':
        arg.T = true;
        break;
      default:
        arg.error = true;
        fprintf(stderr, "Try 'cat --help' for more information.\n");
    }
  }
  return arg;
}

void output(flags arg, int argc, const char *const argv[]) {
  int indx[argc];
  int count_streams = is_stream(indx, argc, argv);
  int i = 0, files_count = 0, lines_count = 1, blank_lines_count = 0;
  char *line = NULL, last_char = 0;
  size_t line_size = 0;
  bool flag = true, first_line = true;
  while (count_streams-- && flag) {
    if (!strcmp(argv[indx[i]], "-") || !strcmp(argv[indx[i]], "--"))
      read_from_stdin(arg, argv[0], line, &line_size, &lines_count,
                      &blank_lines_count, &flag);
    else if (file_check(argv[0], argv[indx[i]]) == 1) {
      read_from_file(arg, argv[0], argv[indx[i]], files_count, line,
                     &first_line, &last_char, &line_size, &lines_count,
                     &blank_lines_count, &flag);
      ++files_count;
    }
    ++i;
  }
  if (i == 0) {
    read_from_stdin(arg, argv[0], line, &line_size, &lines_count,
                    &blank_lines_count, &flag);
  }
}

int is_stream(int *file_index, int argc, const char *const argv[]) {
  int index = 0;
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] != '-' || !strcmp(argv[i], "-") || !strcmp(argv[i], "--"))
      file_index[index++] = i;
  }
  return index;
}

void read_from_stdin(flags arg, const char *cmd, char *line, size_t *line_size,
                     int *lines_count, int *blank_lines_count, bool *flag) {
  int length = get_line(&line, line_size, stdin);
  while (length > 0) {
    output_line(arg, 0, line, false, 0, length, lines_count, blank_lines_count);
    length = get_line(&line, line_size, stdin);
  }
  free(line);
  if (length == -2) {
    fprintf(stderr, "%s: Memory allocation error\n", cmd);
    *flag = false;
  }
}

void read_from_file(flags arg, const char *cmd, const char *const file_name,
                    int files_count, char *line, bool *first_line,
                    char *last_char, size_t *line_size, int *lines_count,
                    int *blank_lines_count, bool *flag) {
  FILE *file = fopen(file_name, "r");
  int length = get_line(&line, line_size, file);
  *first_line = true;
  while (length > 0) {
    output_line(arg, files_count, line, *first_line, *last_char, length,
                lines_count, blank_lines_count);
    *last_char = line[length - 1];
    length = get_line(&line, line_size, file);
    *first_line = false;
    if (length > 0) *last_char = line[length - 1];
  }
  free(line);
  fclose(file);
  if (length == -2) {
    fprintf(stderr, "%s: Memory allocation error\n", cmd);
    *flag = false;
  }
}