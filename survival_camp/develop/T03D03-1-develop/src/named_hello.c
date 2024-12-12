#include <stdio.h>

int main(void) {
    int name;

    if (scanf("%d", &name) != 1) {
        printf("Wrong name!\n");
        return 0;
    }

    printf("Hello, %d!\n", name);
    return 0;
}