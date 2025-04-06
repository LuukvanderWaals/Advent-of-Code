#ifndef STACK_H
#define STACK_H

typedef struct Stack Stack;

Stack *createStack();
int push(Stack *stack, void *data);
void *pop(Stack *stack);
void *peek(Stack *stack);
int isEmpty(Stack *stack);
int size(Stack *stack);
void freeStack(Stack *stack);

#endif