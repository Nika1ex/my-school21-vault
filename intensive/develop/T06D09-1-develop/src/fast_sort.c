#include <stdio.h>
#define NMAX 10

int input(int *a);
void copy_data(int *a, int *b);
void quick_sort(int *a, int left, int right);
void merge_sort(int *a, int size);
void merge(int *left, int size1, int *right, int size2, int *a);
void output(int *a, int *b);

int main() {
    int data1[NMAX];
    int data2[NMAX];
    int flag = input(data1);
    if (flag != NMAX) {
        printf("n/a");
    } else {
        copy_data(data1, data2);
        quick_sort(data1, 0, NMAX - 1);
        merge_sort(data2, NMAX);
        output(data1, data2);
    }
    return 0;
}

int input(int *a) {
    int flag = 0;
    int end = -1;
    int *p = a;
    while (p - a < NMAX && p - flag == a && end != '\n') {
        flag += scanf("%d", p);
        p++;
        end = getchar();
        if (end != '\n' && end != ' ') {
            flag = -1;
        }
    }
    if (end != '\n') {
        flag = -1;
    }
    return flag;
}

void copy_data(int *a, int *b) {
    for (int i = 0; i < NMAX; i++) {
        b[i] = a[i];
    }
}

void quick_sort(int *a, int left, int right) {
    if (left > right) return;
    int p = a[(left + right) / 2];
    int i = left;
    int j = right;
    while (i <= j) {
        while (a[i] < p) i++;
        while (a[j] > p) j--;
        if (i <= j) {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    }
    quick_sort(a, left, j);
    quick_sort(a, i, right);
}

void merge_sort(int *b, int size) {
    if (size <= 1) {
        return;
    }
    int left[size];
    int right[size];
    int middle = size / 2;
    for (int i = 0; i < middle; i++) {
        left[i] = b[i];
    }
    for (int i = middle; i < size; i++) {
        right[i - middle] = b[i];
    }
    merge_sort(left, middle);
    merge_sort(right, size - middle);
    merge(left, middle, right, size - middle, b);
}

void merge(int *left, int size1, int *right, int size2, int *b) {
    int i = 0;
    int k = 0;
    int n = 0;
    while (i < size1 && k < size2) {
        if (left[i] <= right[k]) {
            b[n] = left[i];
            i++;
        } else {
            b[n] = right[k];
            k++;
        }
        n++;
    }
    while (i < size1) {
        b[n] = left[i];
        i++;
        n++;
    }
    while (k < size2) {
        b[n] = right[k];
        k++;
        n++;
    }
}

void output(int *a, int *b) {
    for (int i = 0; i < NMAX; i++) {
        if (i < NMAX - 1) {
            printf("%d ", a[i]);
        } else {
            printf("%d\n", a[i]);
        }
    }
    for (int i = 0; i < NMAX; i++) {
        if (i < NMAX - 1) {
            printf("%d ", b[i]);
        } else {
            printf("%d", b[i]);
        }
    }
}