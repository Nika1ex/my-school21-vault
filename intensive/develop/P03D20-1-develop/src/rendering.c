#include "rendering.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "polish.h"
#define MAX 100

char **memory_allocation_graph() {
    char **graph = (char **)malloc(sizeof(char *) * HEIGHT);
    if (graph != NULL) {
        for (int y = 0; y < HEIGHT; y++) {
            graph[y] = (char *)malloc(sizeof(char) * (WIDTH + 1));
            if (graph[y] == NULL) {
                for (int i = 0; i < y; i++) {
                    free(graph[i]);
                    graph[i] = NULL;
                }
                free(graph);
            }
        }
    }
    return graph;
}

void function_values_array(double *function, char str[MAX][MAX]) {
    double step_x = (4 * M_PI) / (WIDTH - 1);
    for (int i = 0; i < WIDTH; i++) {
        double current_x = i * step_x;
        double y = polish_math(str, current_x);
        function[i] = y;
    }
}

void graph_initialization(char **graph, const double *function) {
    double step_y = 2.0 / (HEIGHT - 1);
    for (int y = 0; y < HEIGHT; y++) {
        double current_y = (-1 + (y * step_y));
        for (int x = 0; x < WIDTH; x++) {
            if (fabs(function[x] - current_y) < step_y / 2)
                graph[y][x] = '*';
            else {
                graph[y][x] = '.';
            }
        }
        graph[y][WIDTH] = '\0';
    }
}

void drawing_graph(char **graph) {
    for (int y = 0; y < HEIGHT; y++) {
        printf("%s\n", graph[y]);
    }
}

void memory_free_up(char **graph) {
    for (int y = 0; y < HEIGHT; y++) {
        free(graph[y]);
        graph[y] = NULL;
    }
    free(graph);
}