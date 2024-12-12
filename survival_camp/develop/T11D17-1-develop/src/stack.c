#include "stack.h"

#include <stdlib.h>

Stack *init(size_t capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    Stack *result;
    if (!stack) {
        result = NULL;
    } else {
        stack->capacity = capacity;
        stack->top = 0;
        stack->data = (int *)malloc(capacity * sizeof(int));
        if (!stack->data) {
            free(stack);
            result = NULL;
        }
        result = stack;
    }
    return result;
}

int push(Stack *stack, int value) {
    int result;
    if (stack->top >= stack->capacity) {
        result = FAIL;
    } else {
        stack->data[stack->top++] = value;
        result = SUCCESS;
    }
    return result;
}

int pop(Stack *stack, int *value) {
    int result;
    if (stack->top == 0) {
        result = FAIL;
    } else {
        *value = stack->data[--stack->top];
        result = SUCCESS;
    }
    return result;
}

void destroy(Stack *stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}