#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

void push_double(double res, stack *s) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%g", res);
    char *str = strdup(buffer);
    push(s, str);
    free(str);
}

double doublestack(stack *s) {
    double x = 0;
    sscanf(pop(s), "%lf", &x);
    return x;
}

double polish_math(char str[100][100], double x) {
    stack s;
    s.top = -1;
    for (int i = 0; str[i][0] != '\0'; i++) {
        if (str[i][0] >= '0' && str[i][0] <= '9')
            push(&s, str[i]);
        else if (str[i][0] == 'x')
            push_double(x, &s);
        else if (strcmp(str[i], "sin") == 0)
            push_double(sin(doublestack(&s)), &s);
        else if (strcmp(str[i], "cos") == 0)
            push_double(cos(doublestack(&s)), &s);
        else if (strcmp(str[i], "tan") == 0)
            push_double(tan(doublestack(&s)), &s);
        else if (strcmp(str[i], "ctg") == 0)
            push_double(1 / tan(doublestack(&s)), &s);
        else if (strcmp(str[i], "sqrt") == 0)
            push_double(sqrt(doublestack(&s)), &s);
        else if (strcmp(str[i], "ln") == 0)
            push_double(log(doublestack(&s)), &s);
        else if (str[i][0] == '+') {
            double a = 0, b = 0;
            sscanf(pop(&s), "%lf", &a);
            sscanf(pop(&s), "%lf", &b);
            push_double(a + b, &s);
        } else if (str[i][0] == '-') {
            double a = 0, b = 0;
            sscanf(pop(&s), "%lf", &a);
            sscanf(pop(&s), "%lf", &b);
            push_double(b - a, &s);
        } else if (str[i][0] == '*') {
            double a = 0, b = 0;
            sscanf(pop(&s), "%lf", &a);
            sscanf(pop(&s), "%lf", &b);
            push_double(a * b, &s);
        } else if (str[i][0] == '/') {
            double a = 0, b = 0;
            sscanf(pop(&s), "%lf", &a);
            sscanf(pop(&s), "%lf", &b);
            if (b != 0) push_double(b / a, &s);
        }
    }

    double rezult = 0;
    sscanf(pop(&s), "%lf", &rezult);
    return rezult;
}