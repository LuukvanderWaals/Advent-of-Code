#ifndef ITERATOR_H
#define ITERATOR_H

typedef struct Iterable Iterable;
typedef struct Iterator Iterator;

Iterator *iterate(void *iterable);
Iterator *createIterator(void *iterable, void *data, void *(*next)(void **), void (*free)(void *));
void *next(Iterator *iter);
int hasNext(Iterator *iter);
void freeIterator(Iterator *iter);

#endif