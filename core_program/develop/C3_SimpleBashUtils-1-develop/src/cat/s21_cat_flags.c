#include "s21_cat.h"

void output_line(flags arg, int files_count, char *line, bool first_line,
                 char last_char, size_t length, int *lines_count,
                 int *blank_lines_count) {
  if (arg.s) s_flag(line, blank_lines_count);
  if (arg.b)
    b_flag(files_count, first_line, last_char, length, lines_count);
  else if (arg.n) {
    if (arg.s && *blank_lines_count > 1)
      return;
    else
      n_flag(files_count, first_line, last_char, lines_count);
  }
  for (size_t i = 0; i < length && *blank_lines_count < 2; ++i) {
    if (arg.v) v_flag(&line[i]);
    if (arg.T) T_flag(&line[i]);
    if (arg.E) E_flag(&line[i]);
    putchar(line[i]);
  }
}

void s_flag(const char *line, int *blank_lines_count) {
  if (line[0] == '\n') {
    (*blank_lines_count)++;
  } else
    *blank_lines_count = 0;
}

void b_flag(int files_count, bool first_line, char last_char, size_t length,
            int *lines_count) {
  if (length > 1) {
    if (!files_count) {
      printf("%6d\t", (*lines_count)++);
    } else if (!first_line || last_char == '\n')
      printf("%6d\t", (*lines_count)++);
  }
}

void n_flag(int files_count, bool first_line, char last_char,
            int *lines_count) {
  if (!files_count)
    printf("%6d\t", (*lines_count)++);
  else if (!first_line || last_char == '\n')
    printf("%6d\t", (*lines_count)++);
}

void v_flag(char *ch) {
  if (*ch == '\n' || *ch == '\t') return;
  if (*ch < 0) {
    printf("M-");
    *ch = *ch & 0b01111111;
  }
  if (*ch < 32) {
    putchar('^');
    *ch += 64;
  } else if (*ch == 127) {
    putchar('^');
    *ch = '?';
  }
}

void T_flag(char *ch) {
  if (*ch == '\t') {
    putchar('^');
    *ch = 'I';
  }
}

void E_flag(char *ch) {
  if (*ch == '\r') {
    putchar('^');
    *ch = 'M';
  }
  if (*ch == '\n') putchar('$');
}