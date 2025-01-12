#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "linkedList.h"
#include "iterator.h"

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
    int res = 0;
    Iterator *iterx = iterate((Iterable *) lx);
    Iterator *itery = iterate((Iterable *) ly);
    x = (long) next(iterx);
    y = (long) next(itery);
    while (x != 0 && y != 0) {
        while (y < x) { y = (long) next(ly); };
        int i = 0;
        while (y == x) {
            i += y;
            y = (long) next(ly);
        }
        int temp = x;
        do {
            res += i;
            x = (long) next(lx);
        } while (x == temp);
    }
    freeIterator(iterx);
    freeIterator(itery);
    printf("%d\n", res);
    freeLinkedList(lx);
    freeLinkedList(ly);
    fclose(file);
    return 0;
}
