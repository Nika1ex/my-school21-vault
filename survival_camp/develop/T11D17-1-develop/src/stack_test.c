#include "stack.h"

#include <stdio.h>

void test_push();
void test_pop();

int main() {
    test_push();
    test_pop();
    return 0;
}

void test_push() {
    Stack *stack = init(2);
    if (push(stack, 1) == SUCCESS && push(stack, 2) == SUCCESS) {
        printf("Push test: SUCCESS\n");
    } else {
        printf("Push test: FAIL\n");
    }
    destroy(stack);
}

void test_pop() {
    Stack *stack = init(2);
    int value;
    push(stack, 1);
    push(stack, 2);
    if (pop(stack, &value) == SUCCESS && value == 2) {
        printf("Pop test: SUCCESS. Popped value: %d\n", value);
    } else {
        printf("Pop test: FAIL\n");
    }
    destroy(stack);
}