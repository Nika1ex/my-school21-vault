#ifndef STACK_H
#define STACK_H
#define MAX 100

typedef struct {
    char str[MAX][MAX];
    int top;
} stack;

char *peek(stack *s);
char *pop(stack *s);
void push(stack *s, const char *item);

#endif