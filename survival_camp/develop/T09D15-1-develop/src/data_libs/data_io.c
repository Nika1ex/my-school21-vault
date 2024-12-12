#include "data_io.h"

#include <stdio.h>

int input(double *data, int n) {
    int flag = 1;
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", &data[i]) != 1) {
            flag = 0;
        }
    }
    if (getchar() != '\n') flag = 0;
    return flag;
}

void output(double *data, int n) {
    for (int i = 0; i < n; i++) {
        if (i < n - 1) {
            printf("%.2lf ", data[i]);
        } else {
            printf("%.2lf", data[i]);
        }
    }
}