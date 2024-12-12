#ifndef S21_COMMON_H
#define S21_COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int file_check(const char *cmd, const char *const file_name);
int get_line(char **lineptr, size_t *n, FILE *stream);

#endif