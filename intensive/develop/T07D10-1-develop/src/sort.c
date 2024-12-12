#include <stdio.h>
#include <stdlib.h>

int input(int *array, int size);
void insert_sort(int *array, int size);
void output(int *array, int size);

int main() {
    int size = 0;
    char w;
    if (scanf("%d%c", &size, &w) == 2 && (w == '\n' || w == ' ' || w == '\0')) {
        int *data = malloc(size * sizeof(int));
        int flag = input(data, size);
        if (!flag) {
            printf("n/a");
            free(data);
        } else {
            insert_sort(data, size);
            output(data, size);
            free(data);
        }
    } else {
        printf("n/a");

        return 0;
    }
}

int input(int *array, int size) {
    int flag = 1;
    for (int p = 0; p < size; p++) {
        if (scanf("%d", &array[p]) != 1) flag = 0;
    }
    if (getchar() != '\n') flag = 0;
    return flag;
}

void insert_sort(int *array, int size) {
    for (int i = 1; i < size; i++) {
        int k = i;
        while (k > 0 && array[k - 1] > array[k]) {
            int tmp = array[k - 1];
            array[k - 1] = array[k];
            array[k] = tmp;
            k -= 1;
        }
    }
}

void output(int *array, int size) {
    for (int i = 0; i < size; i++) {
        if (i < size - 1) {
            printf("%d ", array[i]);
        } else {
            printf("%d", array[i]);
        }
    }
}
