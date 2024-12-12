#include <math.h>
#include <stdio.h>

int finder(double x);
int division(int y, int i);
int simple_divider(int z);

int main(void) {
    double a;
    char b;
    if (scanf("%lf%c", &a, &b) != 2 || a != (int)a || a == 0 || fabs(a) == 1 || b != '\n') {
        printf("n/a\n");
        return 0;
    }
    int res = finder(a);
    printf("%d\n", res);
    return 0;
}

int finder(double x) {
    int q = 2;
    for (int i = 2; i <= fabs(x); i++) {
        if (division(fabs(x), i) && simple_divider(i)) {
            q = i;
        }
    }
    return q;
}

int division(int y, int i) {
    while (y >= 0) {
        y -= i;
        if (y == 0) return 1;
    }
    return 0;
}

int simple_divider(int z) {
    for (int j = 2; j <= z - 1; j++) {
        if (division(z, j)) {
            return 0;
        }
    }
    return 1;
}
