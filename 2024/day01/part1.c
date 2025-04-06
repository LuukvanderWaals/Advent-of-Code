#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../lib/linkedList.h"
#include "../lib/iterator.h"

int comp(void *a, void *b) {
    return (int) (a - b);
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    LinkedList *lx = createLinkedList();
    LinkedList *ly = createLinkedList();
    long x, y;
    while (!feof(file)) {
        fscanf(file, "%ld %ld", &x, &y);
        insertionSort(lx, (void *) x, comp);
        insertionSort(ly, (void *) y, comp);
    }
    Iterator *iterx = iterate((Iterable *) lx);
    Iterator *itery = iterate((Iterable *) ly);
    int res = 0;
    for (int i = 0; i < len(lx); i++) {
        res += abs((int) (next(iterx) - next(itery)));
    }
    freeIterator(iterx);
    freeIterator(itery);
    printf("%d\n", res);
    freeLinkedList(lx);
    freeLinkedList(ly);
    fclose(file);
    return 0;
}
