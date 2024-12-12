#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void test_create_node(int num) {
    tree *node = create_node(num);
    if (node != NULL) {
        printf("SUCCESS! Tree node value %d\n", node->num);
        free(node);
    } else {
        printf("FAIL!\n");
    }
}

int main() {
    test_create_node(0);
    test_create_node(10);
    test_create_node(20);
}