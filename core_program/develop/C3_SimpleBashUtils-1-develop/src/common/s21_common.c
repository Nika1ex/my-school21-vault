#include "s21_common.h"

int file_check(const char *cmd, const char *const file_name) {
  int flag = 1;
  if (access(file_name, F_OK)) {
    fprintf(stderr, "%s: %s: No such file or directory\n", cmd, file_name);
    flag = -1;
  } else if (access(file_name, R_OK)) {
    fprintf(stderr, "%s: %s: Permission denied\n", cmd, file_name);
    flag = -1;
  } else {
    FILE *file = fopen(file_name, "r");
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fclose(file);
    if (!file_size) flag = 0;
  }
  return flag;
}

int get_line(char **lineptr, size_t *n, FILE *stream) {
  int ch;
  char *tmp = NULL;
  size_t length = 0;
  bool flag = true;
  if (*lineptr == NULL || *n == 0) {
    *n = 1024;
    tmp = (char *)malloc(*n);
    if (tmp == NULL) return -2;
    *lineptr = tmp;
  }
  while (flag && (ch = fgetc(stream)) != EOF) {
    ++length;
    if (length == *n) {
      *n = length * 2;
      tmp = (char *)realloc(*lineptr, *n);
      if (tmp == NULL) return -2;
      *lineptr = tmp;
    }
    *(*lineptr + length - 1) = ch;
    if (ch == '\n') flag = false;
  }
  *(*lineptr + length) = '\0';
  if (length == 0 && ch == EOF) return -1;
  return length;
}