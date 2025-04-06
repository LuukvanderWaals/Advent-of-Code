#include <stdio.h>
#include <stdlib.h>
#include "../lib/map.h"
#include "../lib/linkedList.h"
#include "../lib/set.h"
#include "../lib/iterator.h"

typedef struct {
    int x;
    int y;
} Pos;

Pos *createPos(int x, int y) {
    Pos *pos = malloc(sizeof(Pos));
    pos->x = x;
    pos->y = y;
    return pos;
}

int poscmp(Pos *a, Pos *b) {
    if (a->x != b->x) {
        return a->x - b->x;
    }
    return a->y - b->y;
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    Map *map = createMap();
    Set *antinodes = createSet(poscmp);
    Pos cur;
    cur.x = 0;
    cur.y = 0;
    int width = 0;
    while (fgetc(file) != '\n') {
        width++;
    }
    fseek(file, 0, SEEK_END);
    int height = (ftell(file) + 1) / (width + 1);
    fseek(file, 0, SEEK_SET);
    while (1) {
        char c = fgetc(file);
        if (c == '.') {
            cur.x++;
            continue;
        }
        if (c == '\n') {
            cur.x = 0;
            cur.y++;
            continue;
        }
        if (feof(file)) {
            break;
        }
        LinkedList *ll = mapGet(map, (void *) (long) c);
        if (ll == NULL) {
            ll = createLinkedList();
            mapSet(map, (void *) (long) c, ll);
        }
        Iterator *iter = iterate((Iterable *) ll);
        while (hasNext(iter)) {
            Pos *antenna = next(iter);
            int dx = cur.x - antenna->x;
            int dy = cur.y - antenna->y;
            for (int i = 0; i < 2; i++) {
                int x = cur.x, y = cur.y;
                while (x >= 0 && x < width && y >= 0 && y < height) {
                    Pos *antinode = createPos(x, y);
                    if (isInSet(antinodes, antinode)) {
                        free(antinode);
                    } else {
                        setAdd(antinodes, antinode);
                    }
                    x += dx;
                    y += dy;
                }
                dx = -dx;
                dy = -dy;
            }
        }
        freeIterator(iter);
        append(ll, createPos(cur.x, cur.y));
        cur.x++;
    }
    printf("%d\n", setSize(antinodes));
    freeSet(antinodes);
}
