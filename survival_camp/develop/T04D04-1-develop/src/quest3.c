#include <math.h>
#include <stdio.h>

int recursive_function(int x);

int main(void) {
    float a;
    char b;
    if (scanf("%f%c", &a, &b) != 2 || a != (int)a || a < 0 || b != '\n') {
        printf("n/a\n");
        return 0;
    }

    int c = (int)a;
    int res = recursive_function(c);
    printf("%d\n", res);
    return 0;
}

int recursive_function(int x) {
    if (x == 0) {
        return 0;
    } else if (x == 1) {
        return 1;
    } else {
        return recursive_function(x - 1) + recursive_function(x - 2);
    }
}
