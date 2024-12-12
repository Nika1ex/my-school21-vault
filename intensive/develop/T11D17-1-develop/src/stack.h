#ifndef STACK_H
#define STACK_H

#define SUCCESS 1
#define FAIL 0

#include <stdio.h>

typedef struct Stack {
    int *data;
    size_t top;
    size_t capacity;
} Stack;

Stack *init(size_t capacity);
int push(Stack *stack, int value);
int pop(Stack *stack, int *value);
void destroy(Stack *stack);

#endif