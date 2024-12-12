#include "opn_convert.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#define MAX 100

void get_function(char *s) {
    int i = 0;
    char c;
    while ((c = getchar()) != '\n' && i < MAX - 1) {
        s[i++] = c;
    }
    s[i] = '\0';
}

void infix_to_postfix(const char *infix, char result[][MAX], int *num_elements) {
    stack operators;
    operators.top = -1;
    int previous_was_operator = 1;
    while (*infix) {
        if (is_operand(*infix)) {
            char operand[MAX];
            int idx = 0;
            while (is_operand(*infix) || *infix == 'x') operand[idx++] = *infix++;
            operand[idx] = '\0';
            strcpy(result[(*num_elements)++], operand);
            previous_was_operator = 0;
        } else if (is_function(infix, NULL)) {
            int func_len;
            if (is_function(infix, &func_len)) {
                char func[MAX];
                strncpy(func, infix, func_len);
                func[func_len] = '\0';
                push(&operators, func);
                infix += func_len;
                if (*infix == '(') {
                    char op[2] = {*infix, '\0'};
                    push(&operators, op);
                    infix++;
                }
                previous_was_operator = 0;
            }
        } else if (is_operator(*infix)) {
            if (*infix == '-' && previous_was_operator) strcpy(result[(*num_elements)++], "0");
            char op[2] = {*infix++, '\0'};
            while (operators.top != -1 && precedence(peek(&operators)[0]) >= precedence(op[0])) {
                char *top_op = pop(&operators);
                strcpy(result[(*num_elements)++], top_op);
            }
            push(&operators, op);
            previous_was_operator = 1;
        } else if (*infix == '(') {
            char op[2] = {*infix++, '\0'};
            push(&operators, op);
            previous_was_operator = 1;
        } else if (*infix == ')') {
            while (operators.top != -1 && peek(&operators)[0] != '(') {
                char *top_op = pop(&operators);
                strcpy(result[(*num_elements)++], top_op);
            }
            if (operators.top != -1 && peek(&operators)[0] == '(') pop(&operators);
            infix++;
            previous_was_operator = 0;
        } else
            infix++;
    }
    while (operators.top != -1) {
        char *top_op = pop(&operators);
        strcpy(result[(*num_elements)++], top_op);
    }
}

int is_operand(char c) { return ((c >= '0' && c <= '9') || c == 'x' || c == '.'); }

int is_operator(char c) { return (c == '+' || c == '-' || c == '*' || c == '/'); }

int precedence(char c) {
    int flag = 0;
    if (c == '+' || c == '-') {
        flag = 1;
    } else if (c == '*' || c == '/') {
        flag = 2;
    } else {
        flag = 0;
    }
    return flag;
}

int is_function(const char *s, int *func_len) {
    int flag = 0;

    const char *functions[] = {"sin", "cos", "tan", "ctg", "sqrt", "log"};
    int num_functions = sizeof(functions) / sizeof(functions[0]);
    for (int i = 0; i < num_functions; i++) {
        int len = strlen(functions[i]);
        if (strncmp(s, functions[i], len) == 0) {
            if (func_len) {
                *func_len = len;
            }
            flag = 1;
        }
    }
    return flag;
}