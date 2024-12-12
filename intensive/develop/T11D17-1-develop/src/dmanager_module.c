#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(struct door* doors);
void insert_sort(struct door* doors);
void output_doors(struct door* doors);

int main() {
    struct door doors[DOORS_COUNT];

    initialize_doors(doors);
    insert_sort(doors);
    output_doors(doors);

    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void insert_sort(struct door* doors) {
    for (int i = 1; i < DOORS_COUNT; i++) {
        int k = i;
        while (k > 0 && doors[k - 1].id > doors[k].id) {
            int tmp = doors[k - 1].id;
            doors[k - 1].id = doors[k].id;
            doors[k].id = tmp;
            k -= 1;
        }
    }
}

void output_doors(struct door* doors) {
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].status = 0;
        printf("%d, %d", doors[i].id, doors[i].status);
        if (i != DOORS_COUNT - 1) printf("\n");
    }
}