#include <stdio.h>
#include <stdlib.h>

int input_array(int **data, int *capacity, int *lenght);
void output_array(const int *data, int lenght);

int main() {
  int *data = NULL;
  int capacity = 10;
  int lenght = 0;
  int flag = input_array(&data, &capacity, &lenght);
  printf("flag = %d, lenght = %d, capacity = %d\n", flag, lenght, capacity);
  if (flag == -1 && lenght) {
    output_array(data, lenght);
  } else if (flag == 0) {
    printf("n/a");
  }
  free(data);
  return 0;
}

int input_array(int **data, int *capacity, int *lenght) {
  int flag = 1;
  *data = (int *)malloc(sizeof(int) * (*capacity));
  if (*data != NULL) {
    char w;
    int i = 0;
    while (flag == 1) {
      if (scanf("%d%c", &(*data)[i], &w) == 2 &&
          ((*data)[i] > 0 || (*data)[i] == -1) && (w == '\n' || w == ' ')) {
        if ((*data)[i] == -1) {
          flag = -1;
          return flag;
        }
        (*lenght)++;
        if (*lenght == *capacity) {
          *capacity += 10;
          int *tmp = (int *)realloc(*data, sizeof(int) * (*capacity));
          if (tmp != NULL) {
            *data = tmp;
          } else
            flag = 0;
        }
        i++;
      } else
        flag = 0;
    }
  } else
    flag = 0;
  return flag;
}

void output_array(const int *data, int lenght) {
  int count = 0;
  for (int i = 0; i < lenght; i++) {
    if (i % 2 == 0) {
      printf("%d", data[i - count]);
      count++;
    } else
      printf("%d", data[lenght - count]);
    if (i != lenght - 1)
      printf(" ");
  }
}