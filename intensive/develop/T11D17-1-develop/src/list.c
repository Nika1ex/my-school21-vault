#include "list.h"

#include <stdlib.h>

struct node* init(struct door* door) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    struct node* result;
    if (!new_node) {
        result = NULL;
    } else {
        new_node->door = door;
        new_node->next = NULL;
        result = new_node;
    }
    return result;
}

struct node* add_door(struct node* elem, struct door* door) {
    struct node* result;
    if (!elem)
        result = NULL;
    else {
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        if (!new_node)
            result = NULL;
        else {
            new_node->door = door;
            new_node->next = elem->next;
            elem->next = new_node;
            result = new_node;
        }
    }
    return result;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* current = root;
    struct node* result = NULL;
    while (current != NULL) {
        if (current->door->id == door_id) {
            result = current;
        } else {
            current = current->next;
        }
    }
    return result;
}

struct node* remove_door(struct node* elem, struct node* root) {
    struct node* result;
    if (!root || !elem) {
        result = root;
    } else if (root == elem) {
        struct node* next = root->next;
        free(root->door);
        free(root);
        result = next;
    } else {
        struct node* current = root;
        while (current->next && current->next != elem) {
            current = current->next;
        }
        if (current->next == elem) {
            current->next = elem->next;
            free(elem->door);
            free(elem);
        }
        result = root;
    }
    return result;
}

void destroy(struct node* root) {
    struct node* current = root;
    while (current != NULL) {
        struct node* next = current->next;
        free(current->door);
        free(current);
        current = next;
    }
}