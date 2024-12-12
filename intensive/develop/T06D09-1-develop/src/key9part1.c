#include <stdio.h>
#define NMAX 10

int input(int *buffer, int *length);
void output(int *buffer, int number, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *numbers);

int main() {
    int data1[NMAX];
    int data2[NMAX];
    int n = 0;
    int flag = input(data1, &n);
    int sum = sum_numbers(data1, n);
    if (flag != n || n == -1 || sum == 0) {
        printf("n/a");
    } else {
        int res = find_numbers(data1, n, sum, data2);
        output(data2, sum, res);
    }
    return 0;
}

int input(int *buffer, int *length) {
    int flag = scanf("%d", length);
    int end = getchar();
    if (flag == 1 && end == '\n' && *length > 0 && *length <= NMAX) {
        flag = 0;
        end = -1;
        int *p = buffer;
        while (p - buffer < *length && p - flag == buffer && end != '\n') {
            flag += scanf("%d", p);
            p++;
            end = getchar();
            if (end != '\n' && end != ' ') {
                flag = -1;
            }
        }
        if (end != '\n') {
            flag = -1;
        }
    } else {
        flag = -1;
    }
    return flag;
}

int sum_numbers(int *buffer, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum += buffer[i];
        }
    }
    return sum;
}

int find_numbers(int *buffer, int length, int number, int *numbers) {
    int n = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[n] = buffer[i];
            n++;
        }
    }
    return n;
}

void output(int *buffer, int number, int length) {
    printf("%d\n", number);
    for (int i = 0; i < length; i++) {
        if (i < length - 1) {
            printf("%d ", buffer[i]);
        } else {
            printf("%d", buffer[i]);
        }
    }
}