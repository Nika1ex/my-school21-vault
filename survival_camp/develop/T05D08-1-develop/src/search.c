#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
double variance(int *a, int n);
double mean(int *a, int n);
int finder(int *a, int n, double mean_v, double variance_v);

int main() {
    int data[NMAX];
    int n = 0;
    int required_number;
    int flag = input(data, &n);
    if (flag != n || n == -1) {
        printf("n/a");
    } else {
        required_number = finder(data, n, mean(data, n), variance(data, n));
        printf("%d", required_number);
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

int finder(int *a, int n, double mean_v, double variance_v) {
    int required_number = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0 && a[i] >= mean_v && a[i] <= mean_v + 3 * sqrt(variance_v) && a[i] != 0) {
            required_number = a[i];
            break;
        }
    }
    return required_number;
}