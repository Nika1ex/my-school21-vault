#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

void s21_strlen_test(const char *string, size_t lenght);
void s21_strcmp_test(const char *string1, const char *string2, int difference);
void s21_strcpy_test(char *newstring, const char *oldstring);

int main() {
    char *s1 = "Hello, world!";
    char *s2 = "Alex \"29041997!\"";
    char *s3 = NULL;
    char *s4 = "";
    char *s5 = "\0";

#ifdef S21_STRLEN_TEST

    s21_strlen_test(s1, 13);
    s21_strlen_test(s2, 16);
    s21_strlen_test(s3, 0);
    s21_strlen_test(s4, 0);
    s21_strlen_test(s5, 0);

#endif

#ifdef S21_STRCMP_TEST

    s21_strcmp_test(s1, s1, 0);
    s21_strcmp_test(s1, s2, 7);
    s21_strcmp_test(s1, s3, 72);
    s21_strcmp_test(s1, s4, 72);
    s21_strcmp_test(s1, s5, 72);

#endif

#ifdef S21_STRCPY_TEST
    char buf[100];
    s21_strcpy_test(buf, s1);
    s21_strcpy_test(buf, s2);
    s21_strcpy_test(buf, s3);
    s21_strcpy_test(buf, s4);
    s21_strcpy_test(buf, s5);

#endif

    return 0;
}

void s21_strlen_test(const char *string, size_t lenght) {
    printf("%s\n", string);
    printf("%lu\n", s21_strlen(string));
    if (s21_strlen(string) == lenght) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
    printf("\n");
}

void s21_strcmp_test(const char *string1, const char *string2, int difference) {
    printf("%s\n%s\n", string1, string2);
    printf("%d\n", s21_strcmp(string1, string2));
    if (s21_strcmp(string1, string2) == difference) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
    printf("\n");
}

void s21_strcpy_test(char *newstring, const char *oldstring) {
    printf("%s\n%s\n", oldstring, s21_strcpy(newstring, oldstring));
    printf("%d\n", s21_strcmp(newstring, s21_strcpy(newstring, oldstring)));
    if (s21_strcmp(newstring, s21_strcpy(newstring, oldstring)) == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
    printf("\n");
}
