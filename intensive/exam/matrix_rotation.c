#include <stdio.h>

int input_array_size(int *M, int *N);
int input_array(int *array, int M, int N);
void output(int *array, int M, int N);
void output_with_rotate(int *array, int M, int N);

int main(void) {
  int lines;
  int columns;
  int flag_size = 0;
  int flag_array = 0;
  flag_size = input_array_size(&lines, &columns);
  if (flag_size == 1) {
    int data[lines * columns];
    flag_array = input_array(data, lines, columns);
    if (flag_array == 1)
      output_with_rotate(data, lines, columns);
    else
      printf("n/a");
  } else
    printf("n/a");
  return 0;
}

int input_array_size(int *M, int *N) {
  int flag = 1;
  char w;
  if (scanf("%d%d%c", M, N, &w) == 3 && (w == ' ' || w == '\n') && *M > 0 &&
      *N > 0) {
  } else
    flag = 0;
  return flag;
}

int input_array(int *array, int M, int N) {
  int flag = 1;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (scanf("%d", &array[i * N + j]) != 1)
        flag = 0;
    }
  }
  if (getchar() != '\n')
    flag = 0;
  return flag;
}

void output(int *array, int M, int N) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (j != N - 1) {
        printf("%d ", array[i * N + j]);
      } else {
        printf("%d", array[i * N + j]);
      }
    }
    if (i != M - 1) {
      printf("\n");
    }
  }
}

void output_with_rotate(int *array, int M, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = M - 1; j >= 0; j--) {
      if (j != 0) {
        printf("%d ", array[j * N + i]);
      } else {
        printf("%d", array[j * N + i]);
      }
    }
    if (i != N - 1) {
      printf("\n");
    }
  }
}