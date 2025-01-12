#ifndef STACK_H
#define STACK_H

typedef struct Stack Stack;

Stack *createStack();
int push(Stack *, void *);
void *pop(Stack *);
void *peek(Stack *);
int isEmpty(Stack *);
int size(Stack *);
void freeStack(Stack *);

#endif