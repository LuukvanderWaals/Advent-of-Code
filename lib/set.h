#ifndef SET_H
#define SET_H

typedef struct Set Set;

Set *createSet(long (*comp)(void *, void *));
int setAdd(Set *, void *);
void *setRemove(Set *, void *);
void *setGet(Set *, void *);
int isInSet(Set *, void *);
int addSet(Set *, Set *);
int setSize(Set *set);
void freeSet(Set *);

#endif