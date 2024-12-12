#include <stdio.h>

int main() {
  int x = 0, multi = 1, rem = 1, flag = 0;
  char w;

  if (scanf("%d%c", &x, &w) == 2 && w == '\n') {
    if (x < 0)
      x = -x;
    if (x < 10) {
      if (x % 2 != 0 && x != 0) {
        printf("%d", x);
      } else
        printf("0");
    } else {
      while (!(x < 10)) {
        rem = x % 10;
        if (rem % 2 != 0) {
          multi = rem * multi;
          flag++;
        }
        x = x / 10;
      }

      if (x % 2 == 0 && flag)
        printf("%d", multi);
      else {
        if (x % 2 != 0)
          printf("%d", multi * x);
        else
          printf("0");
      }
    }
  } else
    printf("n/a");
  return 0;
}