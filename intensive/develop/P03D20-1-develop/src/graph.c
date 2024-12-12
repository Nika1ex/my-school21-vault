#include <stdio.h>

#include "opn_convert.h"
#include "rendering.h"
#define MAX 100

int main() {
    char **graph = memory_allocation_graph();

    char s[MAX];
    get_function(s);

    char result[MAX][MAX];
    int num_elements = 0;

    infix_to_postfix(s, result, &num_elements);

    if (graph != NULL) {
        double function[WIDTH];
        function_values_array(function, result);
        graph_initialization(graph, function);
        drawing_graph(graph);
        memory_free_up(graph);
    } else {
        printf("Ошибка выделения памяти!\n");
    }
    return 0;
}