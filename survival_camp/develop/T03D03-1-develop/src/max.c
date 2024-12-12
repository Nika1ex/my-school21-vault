#include <stdio.h>

int max(int a, int b);

int main(void) {
    float x, y;
    char z;
    if (scanf("%f %f%c", &x, &y, &z) != 3 || x != (int)x || y != (int)y || z != '\n') {
        printf("n/a\n");
        return 0;
    }

    printf("%d\n", max(x, y));
    return 0;
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}