#include <stdio.h>
#define NMAX 10

int input(int *a);
void insert_sort(int *a);
void output(int *a);

int main() {
    int data[NMAX];
    int flag = input(data);
    if (flag != NMAX) {
        printf("n/a");
    } else {
        insert_sort(data);
        output(data);
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

void insert_sort(int *a) {
    for (int i = 1; i < NMAX; i++) {
        int k = i;
        while (k > 0 && a[k - 1] > a[k]) {
            int tmp = a[k - 1];
            a[k - 1] = a[k];
            a[k] = tmp;
            k -= 1;
        }
    }
}

void output(int *a) {
    for (int i = 0; i < NMAX; i++) {
        if (i < NMAX - 1) {
            printf("%d ", a[i]);
        } else {
            printf("%d", a[i]);
        }
    }
}