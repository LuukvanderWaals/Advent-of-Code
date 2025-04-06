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
    int x = 0, y = 0;
    char c = 0;
    do {
        switch (c) {
            case '^':
                y++;
                break;
            case 'v':
                y--;
                break;
            case '>':
                x++;
                break;
            case '<':
                x--;
                break;
        }
        Coord *coord = malloc(sizeof(Coord));
        coord->x = x;
        coord->y = y;
        set_add(set, coord);
    } while ((c = getc(file)) != EOF);
    printf("%d\n", set_size(set));
}
