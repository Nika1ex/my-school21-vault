#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <string.h>

#include "../common/s21_common.h"

typedef struct {
  int e, i, v, c, l, n, h, s, f, o, error;
  char *pattern;
  size_t pattern_length;
  size_t pattern_memory;
} arguments;

void parse(arguments *arg, int argc, char *const argv[]);
int find_unmatched_regexec(const char *pattern);
int add_pattern(arguments *arg, const char *cmd, const char *pattern);
int obtain_patterns_from_file(arguments *arg, const char *cmd,
                              const char *filepath);
void if_no_flags(arguments *arg, int argc, char *const argv[]);
void output(arguments arg, int argc, const char *const argv[]);
int find_mnemonic_symbols(const char *pattern);
void read_from_file(arguments arg, const char *cmd, const char *filepath,
                    regex_t *regex);
void output_matches(arguments arg, regex_t *regex, const char *filepath,
                    char *line, size_t line_number);
void output_line(const char *line, size_t length);

#endif