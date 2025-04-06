#include "set.h"
#include "iterator.h"
#include "stack.h"
#include <stdlib.h>

typedef struct Node Node;

struct Set {
    Iterator *(*iterate)(Set *);
    int size;
    Node *root;
    long (*comp)(void *, void *);
};

struct Node {
    void *data;
    Node *left;
    Node *right;
};

void *setnext(void **data) {
    Stack *stack = *data;
    Node *node = pop(stack);
    void *res = node->data;
    node = node->right;
    while (node != NULL) {
        push(stack, node);
        node = node->left;
    }
    if (isEmpty(stack)) {
        freeStack(stack);
        *data = NULL;
    }
    return res;
}

void setfreeiterdata(void *data) {
    if (data) {
        freeStack(data);
    }
}

Iterator *setiterate(Set *set) {
    Stack *stack;
    if (set->size == 0) {
        stack = NULL;
    } else {
        stack = createStack();
        Node *node = set->root;
        while (node) {
            push(stack, node);
            node = node->left;
        }
    }
    return createIterator(set, stack, setnext, setfreeiterdata);
}

long stdcomp(void *a, void *b) {
    return a - b;
}

Set *createSet(long (*comp)(void *, void *)) {
    Set *set = calloc(1, sizeof(Set));
    if (set == NULL) {
        return NULL;
    }
    set->iterate = setiterate;
    if (comp == NULL) {
        comp = stdcomp;
    }
    set->comp = comp;
    return set;
}

Node **findNode(Set *set, void *data) {
    Node **node = &set->root;
    while (*(node) != NULL) {
        long d = set->comp(data, (*node)->data);
        if (d == 0) {
            return node;
        }
        if (d < 0) {
            node = &(*node)->left;
        } else {
            node = &(*node)->right;
        }
    }
    return node;
}

int setAdd(Set *set, void *data) {
    Node **node = findNode(set, data);
    if (*node != NULL) {
        return 0;
    }
    *node = calloc(1, sizeof(Node));
    if (*node == NULL) {
        return 1;
    }
    (*node)->data = data;
    set->size++;
    return 0;
}

void *setRemove(Set *set, void *data) {
    Node **node_p = findNode(set, data);
    Node *node = *node_p;
    if (node == NULL) {
        return NULL;
    }
    data = node->data;
    if (node->right == NULL) {
        Node *newNode = node->left;
        *node_p = newNode;
        free(node);
        return data;
    }
    Node **newNode = &node->right;
    while ((*newNode)->left != NULL) {
        newNode = &(*newNode)->left;
    }
    *node_p = *newNode;
    *newNode = (*newNode)->right;
    (*node_p)->left = node->left;
    (*node_p)->right = node->right;
    free(node);
    return data;
}

void *setGet(Set *set, void *data)  {
    Node *node = *findNode(set, data);
    if (node == NULL) {
        return NULL;
    }
    return node->data;
}

int isInSet(Set *set, void *data) {
    Node *node = *findNode(set, data);
    if (node == NULL) {
        return 0;
    }
    return 1;
}

int addSet(Set *a, Set *b) {
    if (a == NULL || b == NULL) {
        return 1;
    }
    if (b->root == NULL) {
        return 0;
    }
    Stack *stack = createStack();
    push(stack, b->root);
    while (!isEmpty(stack)) {
        Node *node = pop(stack);
        if (node->left != NULL) {
            push(stack, node->left);
        }
        if (node->right != NULL) {
            push(stack, node->right);
        }
        if (setAdd(a, node->data) != 0) {
            return 1;
        }
    }
    freeStack(stack);
    return 0;
}

int setSize(Set *set) {
    if (set == NULL) {
        return 0;
    }
    return set->size;
}

void freeSet(Set *set) {
    Stack *stack = createStack();
    if (set->root != NULL) {
        push(stack, set->root);
        while (!isEmpty(stack)) {
            Node *node = pop(stack);
            if (node->left != NULL) {
                push(stack, node->left);
            }
            if (node->right != NULL) {
                push(stack, node->right);
            }
            free(node);
        }
    }
    free(set);
    freeStack(stack);
}
