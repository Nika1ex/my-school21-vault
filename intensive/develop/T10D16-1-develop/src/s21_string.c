#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

size_t s21_strlen(const char *string) {
    size_t length = 0;
    if (string) {
        while (string[length] != '\0') length++;
    }
    return length;
}

int s21_strcmp(const char *string1, const char *string2) {
    int difference = 0;
    if (string1 && string2) {
        while (*string1 && *string1 == *string2) {
            string1++;
            string2++;
        }
        difference = *string1 - *string2;
    }
    if (string1 && !string2) difference = *string1;
    if (!string1 && string2) difference -= *string2;
    return difference;
}

char *s21_strcpy(char *newptr, const char *oldptr) {
    char *ptr = NULL;

    if (oldptr != NULL && newptr != NULL) {
        ptr = newptr;
        while (*oldptr != '\0') {
            *newptr = *oldptr;
            newptr++;
            oldptr++;
        }
        *newptr = '\0';
    }
    return ptr;
}