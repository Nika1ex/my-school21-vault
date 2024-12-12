#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "../yet_another_decision_module/decision.h"

#ifdef DATA_IO_MACRO_H
#include "../data_libs/data_io_macro.h"
#else
#include "../data_libs/data_io.h"
#endif

#ifdef USE_DYNAMIC
#include <dlfcn.h>
int main() {
    double *data;
    int n;
    char w;
    void *libdata_process;
    libdata_process = dlopen("data_process.so", RTLD_LAZY);
    int (*normalization)(double *data, int n) = dlsym(libdata_process, "normalization");
    void (*insert_sort)(double *data, int n) = dlsym(libdata_process, "insert_sort");
    if (scanf("%d%c", &n, &w) == 2 && (w == ' ' || w == '\n') && n > 0) {
        data = malloc(sizeof(double) * (n));

        printf("LOAD DATA...\n");
        if (input(data, n)) {
            printf("RAW DATA:\n\t");
            output(data, n);

            printf("\nNORMALIZED DATA:\n\t");
            normalization(data, n);
            output(data, n);

            printf("\nSORTED NORMALIZED DATA:\n\t");
            insert_sort(data, n);
            output(data, n);

            printf("\nFINAL DECISION:\n\t");

            if (make_decision(data, n)) {
                printf("YES");
            } else {
                printf("NO");
            }
        } else {
            printf("ERROR");
        }
    } else
        printf("ERROR");
    free(data);
    return 0;
}
#else

#include "../data_libs/data_stat.h"
#include "../data_module/data_process.h"

int main() {
    double *data = NULL;
    int n;
    char w;
    if (scanf("%d%c", &n, &w) == 2 && (w == ' ' || w == '\n') && n > 0) {
        data = malloc(sizeof(double) * (n));
        printf("LOAD DATA...\n");

#ifdef DATA_IO_MACRO_H
        INPUT_MACRO(data, n);
#else
        input(data, n);
#endif

        printf("RAW DATA:\n\t");

#ifdef DATA_IO_MACRO_H
        OUTPUT_MACRO(data, n);
#else
        output(data, n);
#endif

        printf("\nNORMALIZED DATA:\n\t");
        (*normalization)(data, n);

#ifdef DATA_IO_MACRO_H
        OUTPUT_MACRO(data, n);
#else
        output(data, n);
#endif

        printf("\nSORTED NORMALIZED DATA:\n\t");
        (*insert_sort)(data, n);

#ifdef DATA_IO_MACRO_H
        OUTPUT_MACRO(data, n);
#else
        output(data, n);
#endif

        printf("\nFINAL DECISION:\n\t");

        if (make_decision(data, n)) {
            printf("YES");
        } else {
            printf("NO");
        }
    } else {
        printf("ERROR");
    }
    free(data);
    return 0;
}
#endif