#ifndef BST_H
#define BST_H

#include <stdio.h>

typedef struct {
    int num;
    struct node *left;
    struct node *right;
} tree;

tree *create_node(int num);

#endif