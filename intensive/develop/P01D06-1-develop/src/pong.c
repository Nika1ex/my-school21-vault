#include <stdio.h>

#define WIDTH 82
#define HEIGHT 27

void clear();
int render(int score_1, int score_2, int ball_x, int ball_y, int left_rocket_y, int right_rocket_y);
int ballMovingX(int ball_x, int ball_direction_x);
int ballMovingY(int ball_y, int ball_direction_y);
void startGame();
void endGame(int score_1);
int ballBounceY(int ball_y, int ball_direction_y);
int left_rocket(char key, int left_rocket_y);
int right_rocket(char key, int right_rocket_y);
int rocketBounce(int ball_y, int ball_x, int left_rocket_y, int right_rocket_y, int ball_direction_x);

int main() {
    startGame();
    return 0;
}

void startGame() {
    int score_1 = 0, score_2 = 0;
    int ball_x = WIDTH / 2 - 1;
    int ball_y = (HEIGHT - 1) / 2;
    int left_rocket_y = (HEIGHT - 1) / 2, right_rocket_y = left_rocket_y;
    int ball_direction_x = 1;
    int ball_direction_y = -1;
    while (score_1 <= 21 || score_2 <= 21) {
        render(score_1, score_2, ball_x, ball_y, left_rocket_y, right_rocket_y);
        printf("Нажмите клавишу: A/Z или K/M для управления ракетками и Space для пропуска хода\n");
        char key;
        key = getchar();
        while (getchar() != '\n') continue;
        if (key == ' ' || key == 'a' || key == 'A' || key == 'z' || key == 'Z' || key == 'k' || key == 'K' ||
            key == 'm' || key == 'M') {
            if (key == 'a' || key == 'A' || key == 'z' || key == 'Z' || key == 'k' || key == 'K' ||
                key == 'm' || key == 'M') {
                left_rocket_y = left_rocket(key, left_rocket_y);
                right_rocket_y = right_rocket(key, right_rocket_y);
            }
            ball_direction_y = ballBounceY(ball_y, ball_direction_y);
            ball_direction_x = rocketBounce(ball_y, ball_x, left_rocket_y, right_rocket_y, ball_direction_x);
            if (ball_x == WIDTH - 2 || ball_x == 1) {
                (ball_x == 1) ? score_2++ : score_1++;
                ball_x = WIDTH / 2 - 1;
                ball_y = (HEIGHT - 1) / 2;
                ball_direction_x *= -1;
                left_rocket_y = (HEIGHT - 1) / 2;
                right_rocket_y = (HEIGHT - 1) / 2;
                render(score_1, score_2, ball_x, ball_y, left_rocket_y, right_rocket_y);
                continue;
            }
            ball_x = ballMovingX(ball_x, ball_direction_x);
            ball_y = ballMovingY(ball_y, ball_direction_y);
            render(score_1, score_2, ball_x, ball_y, left_rocket_y, right_rocket_y);
        }
        if (score_1 == 21 || score_2 == 21) {
            endGame(score_1);
            break;
        }
    }
}

int render(int score_1, int score_2, int ball_x, int ball_y, int left_rocket_y, int right_rocket_y) {
    clear();
    printf("%40d %d\n", score_1, score_2);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1) {
                printf("=");
            } else if (i == ball_y && j == ball_x) {
                printf("o");
            } else if ((j == 1 && i == left_rocket_y) || (j == 1 && i == left_rocket_y - 1) ||
                       (j == 1 && i == left_rocket_y + 1)) {
                printf("|");
            } else if ((j == WIDTH - 2 && i == right_rocket_y) ||
                       (j == WIDTH - 2 && i == right_rocket_y - 1) ||
                       (j == WIDTH - 2 && i == right_rocket_y + 1)) {
                printf("|");
            } else if ((j == 0) || j == WIDTH - 1) {
                printf("*");
            } else if (j == WIDTH / 2 - 1) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}

void clear() {
    for (int i = 0; i < 40; i++) {
        printf("\n");
    }
}

int ballMovingX(int ball_x, int ball_direction_x) {
    ball_x += ball_direction_x;
    return ball_x;
}

int ballMovingY(int ball_y, int ball_direction_y) {
    ball_y += ball_direction_y;
    return ball_y;
}

void endGame(int score_1) {
    if (score_1 >= 21) {
        printf("First player won! Congratulations!\n");
    } else {
        printf("Second player won! Congratulations!\n");
    }
}

int ballBounceY(int ball_y, int ball_direction_y) {
    if (ball_y == 1 || ball_y == 25) {
        ball_direction_y *= -1;
    } else {
        return ball_direction_y;
    }
    return ball_direction_y;
}

int left_rocket(char key, int left_rocket_y) {
    if (key == 'a' || key == 'A') {
        if (left_rocket_y >= 3) {
            left_rocket_y--;
        } else
            return left_rocket_y;
    }
    if (key == 'z' || key == 'Z') {
        if (left_rocket_y <= HEIGHT - 4) {
            left_rocket_y++;
        } else
            return left_rocket_y;
    }
    return left_rocket_y;
}

int right_rocket(char key, int right_rocket_y) {
    if (key == 'k' || key == 'K') {
        if (right_rocket_y >= 3) {
            right_rocket_y--;
        } else
            return right_rocket_y;
    }

    if (key == 'm' || key == 'M') {
        if (right_rocket_y <= HEIGHT - 4) {
            right_rocket_y++;
        } else {
            return right_rocket_y;
        }
    }
    return right_rocket_y;
}

int rocketBounce(int ball_y, int ball_x, int left_rocket_y, int right_rocket_y, int ball_direction_x) {
    if ((ball_y == left_rocket_y && ball_x == 2) || (ball_y == left_rocket_y + 1 && ball_x == 2) ||
        (ball_y == left_rocket_y - 1 && ball_x == 2)) {
        ball_direction_x *= -1;
    } else if ((ball_y == right_rocket_y && ball_x == WIDTH - 3) ||
               (ball_y == right_rocket_y + 1 && ball_x == WIDTH - 3) ||
               (ball_y == right_rocket_y - 1 && ball_x == WIDTH - 3)) {
        ball_direction_x *= -1;
    } else {
        return ball_direction_x;
    }
    return ball_direction_x;
}
