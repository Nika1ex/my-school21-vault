#include "bst.h"

#include <stdio.h>
#include <stdlib.h>

tree *create_node(int num) {
    tree *new_node = (tree *)malloc(sizeof(tree));
    if (new_node != NULL) {
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->num = num;
    }
    return new_node;
}