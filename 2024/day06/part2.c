#include <stdio.h>
#include <stdlib.h>
#include "../lib/set.h"

#include <unistd.h>

typedef struct {
    int x;
    int y;
    int d;
} Pos;

long poscmp(void *va, void *vb) {
    Pos *a = (Pos *) va, *b = (Pos *) vb;
    if (a->x != b->x) {
        return a->x - b->x;
    }
    if (a->y != b->y) {
        return a->y - b->y;
    }
    if (a->d == -1 || b->d == -1) {
        return 0;
    }
    return a->d - b->d;
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    int x = 0, y = 0, width, height;
    Pos start;
    Set *obstacles = createSet(poscmp);
    while (!feof(file)) {
        char c = fgetc(file);
        switch (c) {
            case '#':
                Pos *pos = malloc(sizeof(Pos));
                pos->x = x;
                pos->y = y;
                pos->d = -1;
                setAdd(obstacles, pos);
            case '.':
                x++;
                break;
            case '^':
                start.x = x;
                start.y = y;
                x++;
                break;
            case '\n':
                width = x;
                x = 0;
                y++;
        }
    }
    height = y;
    start.d = 0;
    int res = 0;
    Pos you;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            printf("%d, %d\n", x, y);
            Set *path = createSet(poscmp);
            Set *set = createSet(poscmp);
            Pos obstacle;
            obstacle.x = x;
            obstacle.y = y;
            obstacle.d = -1;
            setAdd(set, &obstacle);
            addSet(set, obstacles);
            you.x = start.x;
            you.y = start.y;
            you.d = start.d;
            while (you.x >= 0 && you.x < width && you.y >= 0 && you.y < height) {
                if (isInSet(path, &you)) {
                    res++;
                    break;
                }
                Pos *pos = malloc(sizeof(Pos));
                pos->x = you.x;
                pos->y = you.y;
                pos->d = you.d;
                setAdd(path, pos);
                switch (you.d) {
                    case 0:
                        you.y--;
                        if (isInSet(set, &you)) {
                            you.y++;
                            you.d = 1;
                        }
                        break;
                    case 1:
                        you.x++;
                        if (isInSet(set, &you)) {
                            you.x--;
                            you.d = 2;
                        }
                        break;
                    case 2:
                        you.y++;
                        if (isInSet(set, &you)) {
                            you.y--;
                            you.d = 3;
                        }
                        break;
                    case 3:
                        you.x--;
                        if (isInSet(set, &you)) {
                            you.x++;
                            you.d = 0;
                        }
                        break;
                }
            }
            freeSet(set);
            freeSet(path);
        }
    }
    printf("%d\n", res);
    return 0;
}
