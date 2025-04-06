#include <stdlib.h>
#include <stdio.h>
#include "set.h"

#define COMP_FUNC int (*)(void *, void *)

typedef struct SetNode SetNode;

struct Set {
    int size;
    SetNode *root;
    int (*comp)(void *, void *);
};

struct SetNode {
    void *data;
    SetNode *left;
    SetNode *right;
    int height;
};

static int standard_comp(void *, void *);
static int _set_add(SetNode **, void *, COMP_FUNC);
static void balance(SetNode **);
static int balance_factor(SetNode *);
static void set_height(SetNode *);
static int get_height(SetNode *);
static void left_left_rotation(SetNode **);
static void left_right_rotation(SetNode **);
static void right_left_rotation(SetNode **);
static void right_right_rotation(SetNode **);
static SetNode *_set_remove(SetNode **, void *data, COMP_FUNC);
static int _in_set(SetNode *, void *, COMP_FUNC);
static void _print_set(SetNode *, const char *);



Set *create_set(int (*comp)(void *, void *)) {
    Set *set = (Set *)calloc(1, sizeof(Set));
    if (set == NULL) {
        return NULL;
    }
    if (comp == NULL) {
        set->comp = standard_comp;
    } else {
        set->comp = comp;
    }
    return set;
}

static int standard_comp(void *a, void *b) {
    return a - b;
}



int set_add(Set *set, void *data) {
    int res = _set_add(&set->root, data, set->comp);
    if (res == SET_SUCCESS) {
        set->size++;
    }
    return res;
}

static int _set_add(SetNode **p_node, void * data, int (*comp)(void *, void *)) {
    SetNode *node = *p_node;
    if (node == NULL) {
        *p_node = (SetNode *)calloc(1, sizeof(SetNode));
        node = *p_node;
        if (node == NULL) {
            return SET_FAILURE;
        }
        node->data = data;
        return SET_SUCCESS;
    }
    int diff = (*comp)(data, node->data);
    if (diff == 0) {
        return SET_ALREADY_EXISTS;
    }
    SetNode **child = diff < 0 ? &node->left : &node->right;
    int res = _set_add(child, data, comp);
    if (res != SET_SUCCESS) {
        return res;
    }
    balance(p_node);
    return SET_SUCCESS;
}

static void balance(SetNode **p_node) {
    SetNode *node = *p_node;
    int bf = balance_factor(node);
    if (bf > 1) {
        if (balance_factor(node->left) >= 0) {
            left_left_rotation(p_node);
        }  else {
            left_right_rotation(p_node);
        }
    } else if (bf < -1) {
        if (balance_factor(node->right) > 0) {
            right_left_rotation(p_node);
        } else {
            right_right_rotation(p_node);
        }
    } else {
        set_height(node);
    }
}

static int balance_factor(SetNode *node) {
    return get_height(node->left) - get_height(node->right);
}

static void set_height(SetNode *node) {
    int lh = get_height(node->left);
    int rh = get_height(node->right);
    node->height = (lh > rh ? lh : rh) + 1;
}

static int get_height(SetNode *node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

static void left_left_rotation(SetNode **p_node) {
    SetNode *node = *p_node;
    SetNode *child = node->left;

    node->left = child->right;
    child->right = node;
    *p_node = child;

    set_height(node);
    set_height(child);
}

static void left_right_rotation(SetNode **p_node) {
    SetNode *node = *p_node;
    SetNode *child = node->left;
    SetNode *newRoot = child->right;

    child->right = newRoot->left;
    newRoot->left = child;
    node->left = newRoot->right;
    newRoot->right = node;
    *p_node = newRoot;

    set_height(node);
    set_height(child);
    set_height(newRoot);
}

static void right_left_rotation(SetNode **p_node) {
    SetNode *node = *p_node;
    SetNode *child = node->right;
    SetNode *newRoot = child->left;

    child->left = newRoot->right;
    newRoot->right = child;
    node->right = newRoot->left;
    newRoot->left = node;
    *p_node = newRoot;

    set_height(node);
    set_height(child);
    set_height(newRoot);
}

static void right_right_rotation(SetNode **p_node) {
    SetNode *node = *p_node;
    SetNode *child = node->right;
    node->right = child->left;
    child->left = node;
    *p_node = child;

    set_height(node);
    set_height(child);
}



void *set_remove(Set *set, void *data) {
    SetNode *node = _set_remove(&set->root, data, set->comp);
    if (!node) {
        return NULL;
    }
    set->size--;
    void *res = node->data;
    // free(node);
    printf("%d\n", res);
    return res;
}

static SetNode *_set_remove(SetNode **p_node, void *data, int (*comp)(void *, void *)) {
    SetNode *node = *p_node;
    if (!node) {
        return NULL;
    }
    int diff = comp(data, node->data);
    if (diff != 0) {
        SetNode *res = _set_remove(diff > 0 ? &node->right : &node->left, data, comp);
        if (res) {
            balance(p_node);
        }
        return res;
    }
    // TODO
    SetNode *next_node = get_next_node(p_node);
    return node;
}

// TODO
SetNode *get_next_node(SetNode **p_node) {
    SetNode *node = *p_node;
    if (!node) {
        return NULL;
    }
    if (node->right);
}



int in_set(Set *set, void *data) {
    return _in_set(set->root, data, set->comp);
}

int _in_set(SetNode *node, void *data, int (*comp)(void *, void *)) {
    if (node == NULL) {
        return 0;
    }
    int diff = comp(data, node->data);
    if (diff == 0) {
        return 1;
    }
    return _in_set(diff > 0 ? node->right : node->left, data, comp);
}

int set_size(Set *set) {
    return set->size;
}

void print_set(Set *set, const char *format) {
    printf("{");
    if (set->root != NULL) {
        _print_set(set->root, format);
    }
    printf("}\n");
}

static void _print_set(SetNode *node, const char *format) {
    if (node->left != NULL) {
        _print_set(node->left, format);
    }
    printf(format, node->data);
    printf(", ");
    if (node->right != NULL) {
        _print_set(node->right, format);
    }
}
