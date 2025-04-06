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
    int width, height;
    while (1) {
        char c = fgetc(file);
        if (c == '.') {
            cur.x++;
            continue;
        }
        if (c == '\n') {
            width = cur.x;
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
            Pos *antinode = createPos(2 * cur.x - antenna->x, 2 * cur.y - antenna->y);
            if (isInSet(antinodes, antinode)) {
                free(antinode);
            } else {
                setAdd(antinodes, antinode);
            }
            antinode = createPos(2 * antenna->x - cur.x, 2 * antenna->y - cur.y);
            if (isInSet(antinodes, antinode)) {
                free(antinode);
            } else {
                setAdd(antinodes, antinode);
            }
        }
        freeIterator(iter);
        append(ll, createPos(cur.x, cur.y));
        cur.x++;
    }
    height = cur.y + 1;
    int res = 0;
    Iterator *iter = iterate((Iterable *) antinodes);
    while (hasNext(iter)) {
        Pos *pos = next(iter);
        res += pos->x >= 0 && pos->x < width && pos->y >= 0 && pos->y < height;
    }
    printf("%d\n", res);
    freeSet(antinodes);
}
