#include "iterator.h"
#include <stdlib.h>
#include <stdio.h>

struct Iterator {
    void *data;
    void *(*next)(void **);
    void (*free)(void *);
};

struct Iterable {
    Iterator *(*iterate)(Iterable *);
};

Iterator *iterate(void *iterable) {
    if (iterable == NULL) {
        return NULL;
    }
    Iterator *iter = ((Iterable *) iterable)->iterate(iterable);
    return iter;
};

Iterator *createIterator(void *iterable, void *data, void *(*next)(void **), void (*free)(void *)) {
    Iterator *iter = malloc(sizeof(Iterator));
    iter->data = data;
    iter->next = next;
    iter->free = free;
    return iter;
}

void *next(Iterator *iter) {
    return iter->next(&iter->data);
}

int hasNext(Iterator *iter) {
    return iter->data != NULL;
}

void freeIterator(Iterator *iter) {
    if (iter->free) {
        iter->free(iter->data);
    }
    free(iter);
}
