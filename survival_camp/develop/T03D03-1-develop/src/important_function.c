#include <math.h>
#include <stdio.h>

float func(float x);

int main(void) {
    float a;
    char b;
    if (scanf("%f%c", &a, &b) != 2 || a == 0 || b != '\n') {
        printf("n/a\n");
        return 0;
    }

    printf("%.1f\n", func(a));
    return 0;
}

float func(float x) {
    float y = 7 * pow(10, -3) * pow(x, 4) + ((22.8 * cbrt(x) - pow(10, 3)) * x + 3) / (x * x / 2) -
              x * pow(10 + x, 2 / x) - 1.01;
    return y;
}
