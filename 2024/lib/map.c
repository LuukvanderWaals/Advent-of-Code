#include "map.h"
#include "iterator.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;

struct Map {
    Iterator *(*iterate)(Map *);
    long size;
    Node *root;
    long (*comp)(void *, void *);
};

struct Node {
    void *key;
    void *value;
    Node *left;
    Node *right;
};

long stdcmp(void *a, void *b) {
    return a - b;
}

void *map_next(void **data) {
    Stack *stack = *data;
    Node *node = pop(stack);
    void *rv = node->key;
    node = node->right;
    while (node != NULL) {
        push(stack, node);
        node = node->left;
    }
    if (isEmpty(stack)) {
        freeStack(stack);
        *data = NULL;
    }
    return rv;
}

void map_free_iterator(void *data) {
    if (data) {
        freeStack(data);
    }
}

Iterator *iterate_map(Map *map) {
    Stack *stack;
    if (map->size == 0) {
        stack = NULL;
    } else {
        stack = createStack();
        Node *node = map->root;
        while (node) {
            push(stack, node);
            node = node->left;
        }
    }
    return createIterator(map, stack, map_next, map_free_iterator);
}

Map *create_map(long (*comp)(void *, void *)) {
    Map *map = calloc(1, sizeof(Map));
    if (map == NULL) {
        return NULL;
    }
    map->iterate = iterate_map;
    if (comp == NULL) {
        comp = stdcmp;
    }
    map->comp = comp;
    return map;
}

Node **find_node(Map *map, void *key) {
    Node **node = &map->root;
    while (*(node) != NULL) {
        long d = map->comp(key, (*node)->key);
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

int map_set(Map *map, void *key, void *value) {
    Node **node = find_node(map, key);
    if (*node == NULL) {
        *node = calloc(1, sizeof(Node));
        if (*node == NULL) {
            return 1;
        }
        (*node)->key = key;
        map->size++;
    }
    (*node)->value = value;
    return 0;
}

void *map_get(Map *map, void *key)  {
    Node *node = *find_node(map, key);
    if (node == NULL) {
        return NULL;
    }
    return node->value;
}

long map_size(Map *map) {
    return map->size;
}

void free_map(Map *map) {
    Stack *stack = createStack();
    if (map->root != NULL) {
        push(stack, map->root);
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
    free(map);
    freeStack(stack);
}
