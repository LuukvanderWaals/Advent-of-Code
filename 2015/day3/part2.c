#include <stdio.h>
#include <stdlib.h>
#include "../lib/set.h"

typedef struct {
    int x;
    int y;
} Coord;

int comp_coords(Coord *a, Coord *b) {
    if (a->x - b->x != 0) {
        return a->x - b->x;
    }
    return a->y - b->y;
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    Set *set = create_set(&comp_coords);
    int x[] = {0, 0}, y[] = {0, 0};
    char c = 0;
    int i = 0;
    do {
        switch (c) {
            case '^':
                y[i]++;
                break;
            case 'v':
                y[i]--;
                break;
            case '>':
                x[i]++;
                break;
            case '<':
                x[i]--;
                break;
        }
        Coord *coord = malloc(sizeof(Coord));
        coord->x = x[i];
        coord->y = y[i];
        set_add(set, coord);
        i = (i + 1) % 2;
    } while ((c = getc(file)) != EOF);
    printf("%d\n", set_size(set));
}
