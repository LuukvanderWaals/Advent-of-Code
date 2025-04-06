#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/linkedList.h"
#include "../lib/map.h"

typedef struct {
    int pos;
    int dir;
    int dist;
} Pos;

int distcmp(void *a, void *b) {
    return ((Pos *) a)->dist - ((Pos *) b)->dist;
}

long poscmp(void *a, void *b) {
    Pos *pa = a;
    Pos *pb = b;
    if (pa->pos != pb->pos) {
        return pa->pos - pb->pos;
    }
    return pa->dir - pb->dir;
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    fseek(file, 0, SEEK_END);
    char arr[ftell(file) + 1];
    rewind(file);
    fread(arr, sizeof(char), sizeof(arr) - 1, file);
    fclose(file);
    arr[sizeof(arr) - 1] = '\0';
    int width = strstr(arr, "\n") - arr + 1;
    int height = width / sizeof(arr);
    int end = strstr(arr, "E") - arr;
    Pos *pos = malloc(sizeof(Pos));
    pos->pos = strstr(arr, "S") - arr;
    pos->dir = 0;
    pos->dist = 0;
    int delta[] = {1, -width, -1, width};
    LinkedList *ll = createLinkedList();
    Map *map = createMap();
    while (pos->pos != end) {
        printf("\n-----%d, %d, %d\n", pos->pos, pos->dir, pos->dist);
        Pos *newPos = malloc(sizeof(Pos));
        newPos->pos = pos->pos;
        newPos->dir = (pos->dir + 1) & 3;
        newPos->dist = pos->dist + 1000;
        insertionSort(ll, newPos, distcmp);
        newPos = malloc(sizeof(Pos));
        newPos->pos = pos->pos;
        newPos->dir = (pos->dir + 3) & 3;
        newPos->dist = pos->dist + 1000;
        insertionSort(ll, newPos, distcmp);
        if (arr[pos->pos + delta[pos->dir]] != '#') {
            newPos = malloc(sizeof(Pos));
            newPos->pos = pos->pos + delta[pos->dir];
            newPos->dir = pos->dir;
            newPos->dist = pos->dist + 1;
            insertionSort(ll, newPos, distcmp);
        }
        pos = delete(ll, 0);
        if (pos == NULL) {
            printf("error\n");
            return 1;
        }
    }
    printf("%d\n", pos->dist);
}
