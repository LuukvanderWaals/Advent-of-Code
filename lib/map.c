#include "map.h"
#include <stdlib.h>
#include "set.h"
#include <stdio.h>
#include <string.h>

struct Map {
    long size;
    Set *set;
};

typedef struct {
    void *key;
    void *value;
} Pair;

long comp(void *a, void *b) {
    // return ((Pair *) a)->key - ((Pair *) b)->key;
    return strcmp(((Pair *) a)->key, ((Pair *) b)->key);
}

Map *createMap() {
    Map *map = malloc(sizeof(Map));
    map->size = 0;
    map->set = createSet(comp);
    return map;
}

int mapSet(Map *map, void *key, void *value) {
    Pair keypair;
    keypair.key = key;
    Pair *pair = setGet(map->set, &keypair);
    if (pair != NULL) {
        pair->value = value;
        return 0;
    }
    pair = malloc(sizeof(Pair));
    if (pair == NULL) {
        return 1;
    }
    pair->key = key;
    pair->value = value;
    if (setAdd(map->set, pair) != 0) {
        free(pair);
        return 1;
    }
    return 0;
}

void *mapGet(Map *map, void *key) {
    if (map == NULL) {
        return NULL;
    }
    Pair keypair;
    keypair.key = key;
    Pair *pair = setGet(map->set, &keypair);
    if (pair == NULL) {
        return NULL;
    }
    return pair->value;
}

int isInMap(Map *map, void *key) {
    Pair keypair;
    keypair.key = key;
    return isInSet(map->set, &keypair);
}
