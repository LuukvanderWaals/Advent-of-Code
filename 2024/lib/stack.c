#include "stack.h"
#include <stdlib.h>

typedef struct Node Node;

struct Stack {
    int size;
    Node *top;
};

struct Node {
    void *data;
    Node *next;
};

Stack *createStack() {
    return calloc(1, sizeof(Stack));
}

int push(Stack *stack, void *data) {
    if (stack == NULL) {
        return 1;
    }
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return 1;
    }
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
    return 0;
}

void *pop(Stack *stack) {
    Node *node = stack->top;
    void *data = node->data;
    stack->top = node->next;
    stack->size--;
    free(node);
    return data;
}

void *peek(Stack *stack) {
    return stack->top->data;
}

int isEmpty(Stack *stack) {
    return stack->top == NULL;
}

int size(Stack *stack) {
    return stack->size;
}

void freeStack(Stack *stack) {
    Node *node = stack->top;
    Node *next;
    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }
    free(stack);
}
