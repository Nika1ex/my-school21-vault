#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);
void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int data[NMAX];
    int n = 0;
    int flag = input(data, &n);
    if (flag != n || n == -1) {
        printf("n/a");
    } else {
        output(data, n);
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
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
            printf("%d\n", a[i]);
        }
    }
}

int max(int *a, int n) {
    int max_v = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max_v) max_v = a[i];
    }
    return max_v;
}

int min(int *a, int n) {
    int min_v = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min_v) min_v = a[i];
    }
    return min_v;
}

double mean(int *a, int n) {
    double mean_v = 0;
    for (int i = 0; i < n; i++) {
        mean_v += a[i];
    }
    return mean_v / n;
}
double variance(int *a, int n) {
    double variance_v = 0;
    for (int i = 0; i < n; i++) {
        variance_v += (a[i] - mean(a, n)) * (a[i] - mean(a, n));
    }
    return variance_v / n;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}