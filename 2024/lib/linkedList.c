#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include "iterator.h"

typedef struct Node Node;

struct LinkedList {
    Iterator *(*iterate)(LinkedList *);
    int len;
    Node *p;
    Node *head;
    Node *last;
};

struct Node {
    void *data;
    Node *prev;
    Node *next;
};

void *llnext(void **data) {
    Node *node = *data;
    *data = node->next;
    return node->data;
}

Iterator *lliterate(LinkedList *ll) {
    return createIterator(ll, ll->head, llnext, NULL);
}

LinkedList *createLinkedList() {
    LinkedList *ll = calloc(1, sizeof(LinkedList));
    ll->iterate = lliterate;
    return ll;
}

void freeLinkedList(LinkedList *ll) {
    Node *node = ll->head;
    Node *next;
    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }
    free(ll);
}

int prepend(LinkedList *ll, void *data) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        return 1;
    }
    n->data = data;
    n->prev = NULL;
    n->next = ll->head;
    if (ll->len == 0) {
        ll->last = n;
    } else {
        ll->head->prev = n;
    }
    ll->head = n;
    ll->len++;
    return 0;
}

int append(LinkedList *ll, void *data) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        return 1;
    }
    n->data = data;
    n->prev = ll->last;
    n->next = NULL;
    if (ll->len == 0) {
        ll->head = n;
    } else {
        ll->last->next = n;
    }
    ll->last = n;
    ll->len++;
    return 0;
}

int insertionSort(LinkedList *ll, void *data, int (*comp)(void *, void *)) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        return 1;
    }
    n->data = data;
    ll->len++;
    if (ll->len == 1) {
        n->prev = NULL;
        n->next = NULL;
        ll->head = n;
        ll->last = n;
        return 0;
    }
    Node *p = ll->head;
    while (p != NULL) {
        if ((*comp)(n->data, p->data) <= 0) {
            if (p->prev == NULL) {
                n->prev = NULL;
                ll->head = n;
            } else {
                n->prev = p->prev;
                p->prev->next = n;
            }
            n->next = p;
            p->prev = n;
            return 0;
        }
        p = p->next;
    }
    n->prev = ll->last;
    n->next = NULL;
    ll->last->next = n;
    ll->last = n;
    return 0;
}

void *delete(LinkedList *ll, int index) {
    Node *node;
    if (index == -1) {
        node = ll->last;
    } else {
        if (index < 0) {
            index = ll->len + index;
        }
        if (index < 0 || index >= ll->len) {
            return NULL;
        }
        node = ll->head;
        for (int i = 0; i < index; i++) {
            node = node->next;
        }
    }
    void *data = node->data;
    if (node->prev == NULL) {
        ll->head = node->next;
    } else {
        node->prev->next = node->next;
    }
    if (node->next == NULL) {
        ll->last = node->prev;
    } else {
        node->next->prev = node->prev;
    }
    free(node);
    ll->len--;
    return data;
}

int linkedListSize(LinkedList *ll) {
    return ll->len;
}

void printLinkedList(LinkedList *linkedList) {
    Node *node = linkedList->head;
    if (node == NULL) {
        printf("{}");
        return;
    }
    printf("{");
    while (1) {
        printf("%ld", (long) node->data);
        node = node->next;
        if (node == NULL) {
            break;
        }
        printf(", ");
    }
    printf("}\n");

}

int len(LinkedList *ll) {
    return ll->len;
}

// void *next(LinkedList *ll) {
//     if (ll->p == NULL) {
//         return NULL;
//     }
//     void *data = ll->p->data;
//     ll->p = ll->p->next;
//     return data;
// }
