#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <string.h>

#include "../common/s21_common.h"

typedef struct {
  bool b, v, E, n, s, T, error;
} flags;

flags parse(int argc, char *const argv[]);
void output(flags arg, int argc, const char *const argv[]);
int is_stream(int *file_index, int argc, const char *const argv[]);
void read_from_stdin(flags arg, const char *cmd, char *line, size_t *line_size,
                     int *lines_count, int *blank_lines_count, bool *flag);
void read_from_file(flags arg, const char *cmd, const char *const file_name,
                    int files_count, char *line, bool *first_line,
                    char *last_char, size_t *line_size, int *lines_count,
                    int *blank_lines_count, bool *flag);
void output_line(flags arg, int files_count, char *line, bool first_line,
                 char last_char, size_t length, int *lines_count,
                 int *blank_lines_count);
void s_flag(const char *line, int *blank_lines_count);
void b_flag(int files_count, bool first_line, char last_char, size_t length,
            int *lines_count);
void n_flag(int files_count, bool first_line, char last_char, int *lines_count);
void v_flag(char *ch);
void T_flag(char *ch);
void E_flag(char *ch);

#endif