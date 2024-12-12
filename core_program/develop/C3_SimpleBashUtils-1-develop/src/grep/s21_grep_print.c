#include "s21_grep.h"

void output_matches(arguments arg, regex_t *regex, const char *filepath,
                    char *line, size_t line_number) {
  regmatch_t match;
  int offset = 0;
  while (1) {
    int eflags = 0;
    if (offset > 0) eflags |= REG_NOTBOL;
    int result = regexec(regex, line + offset, 1, &match, eflags);
    if (result) break;
    if (!arg.h) printf("%s:", filepath);
    if (arg.n) printf("%zu:", line_number);
    for (int i = match.rm_so; i < match.rm_eo; ++i) putchar(line[offset + i]);
    putchar('\n');
    offset += match.rm_eo;
  }
}

void output_line(const char *line, size_t length) {
  for (size_t i = 0; i < length; ++i) putchar(line[i]);
  if (line[length - 1] != '\n') putchar('\n');
}