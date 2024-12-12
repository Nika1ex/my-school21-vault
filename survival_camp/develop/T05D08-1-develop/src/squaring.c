#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int data[NMAX];
    int n = 0;
    int flag = input(data, &n);
    if (flag != n || n == -1) {
        printf("n/a");
    } else {
        squaring(data, n);
        output(data, n);
    }
    return 0;
}

int input(int *a, int *n) {
    int flag = scanf("%d", n);
    int end = getchar();
    if (flag == 1 && end == '\n' && *n > 0 && *n <= NMAX) {
        flag = 0;
        end = -1;
        int *p = a;
        while (p - a < *n && end != '\n') {
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
    } else {
        flag = -1;
    }
    return flag;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i < n - 1) {
            printf("%d ", a[i]);
        } else {
            printf("%d", a[i]);
        }
    }
}

void squaring(int *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = a[i] * a[i];
    }
}
