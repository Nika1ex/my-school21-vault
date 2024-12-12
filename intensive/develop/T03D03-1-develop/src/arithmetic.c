#include <stdio.h>

int sum(int a, int b);
int dif(int a, int b);
int mul(int a, int b);
int div(int a, int b);

int main(void) {
    float x, y;
    char z;
    if (scanf("%f %f%c", &x, &y, &z) != 3 || x != (int)x || y != (int)y || z != '\n') {
        printf("n/a\n");
        return 0;
    }

    printf("%d %d %d ", sum(x, y), dif(x, y), mul(x, y));

    if (y == 0) {
        printf("n/a\n");
    } else {
        printf("%d\n", div(x, y));
    }

    return 0;
}

int sum(int a, int b) { return a + b; }

int dif(int a, int b) { return a - b; }

int mul(int a, int b) { return a * b; }

int div(int a, int b) { return a / b; }