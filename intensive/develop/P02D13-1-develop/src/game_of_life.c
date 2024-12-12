#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define height 25
#define width 80

void interactive(void);
void init_ncurses();
int neighbors(const int *matrix, int i, int j);
int survival(int neighbors_count, int live);
void input(int *marix);
void output(const int *marix);
void copi(const int *marix, int *marix2);

int main(void) {
    init_ncurses();
    interactive();
    endwin();
    return 0;
}

void interactive(void) {
    int speed = 1000;
    char key = ' ';

    int *matrix = (int *)calloc(height * width, sizeof(int));
    int *matrix2 = (int *)calloc(height * width, sizeof(int));

    input(matrix);

    while (key != 'q') {
        clear();
        copi(matrix, matrix2);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                matrix2[i * width + j] = survival(neighbors(matrix, i, j), matrix[i * width + j]);
            }
        }
        output(matrix);
        copi(matrix2, matrix);
        key = getch();

        if (key == '+' && speed > 100) speed -= 100;
        if (key == '-' && speed < 2500) speed += 100;

        usleep(speed * 200);
    }
    free(matrix);
    free(matrix2);
}

void init_ncurses() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);
}

int neighbors(const int *matrix, int i_cord, int j_cord) {
    int count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) continue;
            int ni = (i_cord + i + height) % height;
            int nj = (j_cord + j + width) % width;
            count += matrix[ni * width + nj];
        }
    }
    return count;
}

int survival(int neighbors_count, int live) {
    int status = 0;
    if ((neighbors_count == 2 || neighbors_count == 3) && live == 1) {
        status = 1;
    } else if (neighbors_count == 3 && live == 0) {
        status = 1;
    } else {
        status = 0;
    }
    return status;
}

void input(int *matrix) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            scanf("%d", &matrix[i * width + j]);
        }
    }
}

void output(const int *matrix) {
    for (int i = 0; i < height; i++) {
        printw("\n");
        for (int j = 0; j < width; j++) {
            if (matrix[i * width + j] == 0) {
                printw("%s", "-");
            } else {
                printw("%s", "0");
            }
        }
    }
}

void copi(const int *matrix, int *matrix2) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix2[i * width + j] = matrix[i * width + j];
        }
    }
}