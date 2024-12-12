#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdio.h>
#include <stdlib.h>

size_t s21_strlen(const char *string);
int s21_strcmp(const char *string1, const char *string2);
char *s21_strcpy(char *newptr, const char *oldptr);

#endif