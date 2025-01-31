#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "../data_libs/data_stat.h"
#include "data_process.h"

int main() {
    double *data = NULL;
    int n;
    char w;
    if (scanf("%d%c", &n, &w) == 2 && (w == ' ' || w == '\n') && n > 0) {
        data = malloc(sizeof(double) * (n));
        if (input(data, n)) {
            if (normalization(data, n)) {
                output(data, n);
            } else {
                printf("ERROR");
            }
        } else {
            printf("ERROR");
        }
    } else
        printf("ERROR");
    free(data);
    return 0;
}
