#include "print_module.h"

#include <stdio.h>
#include <time.h>

char print_char(char ch) { return putchar(ch); }

void print_log(char (*print)(char), char* message) {
    time_t mytime = time(NULL);
    struct tm* now = localtime(&mytime);
    printf("[LOG] %d:%d:%d ", now->tm_hour, now->tm_min, now->tm_sec);
    while (*message != '\0') {
        print(*message);
        message++;
    }
}
