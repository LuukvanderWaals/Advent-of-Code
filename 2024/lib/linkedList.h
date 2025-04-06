#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedList LinkedList;

LinkedList *createLinkedList();
void freeLinkedList(LinkedList *);

int prepend(LinkedList *, void *);
int append(LinkedList *, void *);
int insertionSort(LinkedList *, void *, int (*)(void *, void *));
void *delete(LinkedList *ll, int index);
int linkedListSize(LinkedList *ll);
void printLinkedList(LinkedList *linkedList);
int len(LinkedList *);

#endif