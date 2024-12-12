#ifndef RENDERING_H
#define RENDERING_H

#define WIDTH 80
#define HEIGHT 25
#define MAX 100

char** memory_allocation_graph();
void function_values_array(double* function, char str[MAX][MAX]);
void graph_initialization(char** graph, const double* function);
void drawing_graph(char** graph);
void memory_free_up(char** graph);

#endif