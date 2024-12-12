#include <stdio.h>

#define INPUT_MACRO(data, n)          \
    do {                              \
        for (int i = 0; i < n; i++) { \
            scanf("%lf", &data[i]);   \
        }                             \
    } while (0)

#define OUTPUT_MACRO(data, n)              \
    do {                                   \
        for (int i = 0; i < n; i++) {      \
            if (i == n - 1) {              \
                printf("%.2lf", data[i]);  \
            } else {                       \
                printf("%.2lf ", data[i]); \
            }                              \
        }                                  \
    } while (0)
