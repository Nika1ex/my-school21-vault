#include <math.h>
#include <stdio.h>
#define NMAX 10

int input(int *buffer, int *length, int *shift);
void shift_data(int *buffer, int length, int shift);
void output(int *buffer, int length);

int main() {
    int data[NMAX];
    int n = 0;
    int c = 0;
    int flag = input(data, &n, &c);
    if (flag != n || n == -1) {
        printf("n/a");
    } else {
        shift_data(data, n, c);
        output(data, n);
    }
    return 0;
}

int input(int *buffer, int *length, int *shift) {
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
        } else {
            if (scanf("%d", shift) != 1 || getchar() != '\n') {
                flag = -1;
            }
        }
    } else {
        flag = -1;
    }
    return flag;
}

void shift_data(int *buffer, int length, int shift) {
    int tmp[length];
    for (int i = 0; i < length; i++) {
        tmp[i] = buffer[i];
    }
    if (shift >= 0) {
        if (shift > length) {
            shift = shift % length;
        }
        for (int i = 0; i < length; i++) {
            if (i + shift < length) {
                buffer[i] = tmp[i + shift];
            } else {
                buffer[i] = tmp[shift - (length - i)];
            }
        }
    } else {
        shift = -shift;
        if (shift > length) {
            shift = shift % length;
        }
        for (int i = 0; i < length; i++) {
            if (shift > i) {
                buffer[i] = tmp[length - (shift - i)];
            } else {
                buffer[i] = tmp[i - shift];
            }
        }
    }
}

void output(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        if (i < length - 1) {
            printf("%d ", buffer[i]);
        } else {
            printf("%d", buffer[i]);
        }
    }
}