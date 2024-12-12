#include "stack.h"

#include <stdio.h>
#include <string.h>

void push(stack *s, const char *item) {
    if (s->top < MAX - 1) {
        strcpy(s->str[++(s->top)], item);
    } else {
        printf("Stack overflow\n");
    }
}

char *pop(stack *s) {
    char *flag = NULL;
    if (s->top >= 0)
        flag = s->str[(s->top)--];
    else
        printf("Stack underflow\n");
    return flag;
}

char *peek(stack *s) {
    char *flag = NULL;

    if (s->top >= 0) flag = s->str[s->top];
    return flag;
}