#include <stdio.h>

int main(void) {
    float x, y;
    char z;

    if (scanf("%f %f%c", &x, &y, &z) != 3 || z != '\n') {
        printf("n/a\n");
        return 0;
    }
    if (x * x + y * y < 25)
        printf("GOTCHA\n");
    else {
        printf("MISS\n");
    }
    return 0;
}
