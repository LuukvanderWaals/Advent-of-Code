#include <stdio.h>
#include <stdlib.h>
#include "../lib/set.h"

typedef struct {
    int x;
    int y;
} Pos;

long poscmp(void *va, void *vb) {
    Pos *a = (Pos *) va, *b = (Pos *) vb;
    if (a->x != b->x) {
        return a->x - b->x;
    }
    return a->y - b->y;
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    int x = 0, y = 0, width, height;
    Pos you;
    Set *obstacles = createSet(poscmp);
    while (!feof(file)) {
        char c = fgetc(file);
        switch (c) {
            case '#':;
                Pos *pos = malloc(sizeof(Pos));
                pos->x = x;
                pos->y = y;
                setAdd(obstacles, pos);
            case '.':
                x++;
                break;
            case '^':
                you.x = x;
                you.y = y;
                x++;
                break;
            case '\n':
                width = x;
                x = 0;
                y++;
        }
    }
    height = y;
    char d = 'u';
    Set *path = createSet(poscmp);
    while (you.x >= 0 && you.x < width && you.y >= 0 && you.y < height) {
        Pos *pos = malloc(sizeof(Pos));
        pos->x = you.x;
        pos->y = you.y;
        setAdd(path, pos);

        switch (d) {
            case 'u':
                you.y--;
                if (isInSet(obstacles, &you)) {
                    you.y++;
                    d = 'r';
                }
                break;
            case 'r':
                you.x++;
                if (isInSet(obstacles, &you)) {
                    you.x--;
                    d = 'd';
                }
                break;
            case 'd':
                you.y++;
                if (isInSet(obstacles, &you)) {
                    you.y--;
                    d = 'l';
                }
                break;
            case 'l':
                you.x--;
                if (isInSet(obstacles, &you)) {
                    you.x++;
                    d = 'u';
                }
                break;
        }
    }
    printf("%d\n", setSize(path));
    return 0;
}
