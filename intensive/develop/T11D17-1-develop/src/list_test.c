#include "list.h"

#include <stdio.h>
#include <stdlib.h>

void test_add_door();
void test_remove_door();

int main() {
    test_add_door();
    test_remove_door();
    return 0;
}

void test_add_door() {
    struct door *door1 = (struct door *)malloc(sizeof(struct door));
    door1->id = 1;
    struct node *list = init(door1);
    struct door *door2 = (struct door *)malloc(sizeof(struct door));
    door2->id = 2;
    add_door(list, door2);
    if (list->next && list->next->door->id == 2) {
        printf("Add_door test: SUCCESS\n");
    } else {
        printf("Add_door test: FAIL\n");
    }
    destroy(list);
}

void test_remove_door() {
    struct door *door1 = (struct door *)malloc(sizeof(struct door));
    door1->id = 1;
    struct node *list = init(door1);
    struct door *door2 = (struct door *)malloc(sizeof(struct door));
    door2->id = 2;
    add_door(list, door2);
    list = remove_door(list->next, list);
    if (list->next == NULL && list->door->id == 1) {
        printf("Remove_door test: SUCCESS\n");
    } else {
        printf("Remove_door test: FAIL\n");
    }
    destroy(list);
}