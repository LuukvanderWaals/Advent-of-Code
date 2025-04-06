#ifndef MAP_H
#define MAP_H

typedef struct Map Map;
typedef struct {
	void *key;
	void *value;
} Pair;

Map *create_map(long (*comp)(void *, void *));
int map_set(Map *map, void *key, void *value);
void *map_get(Map *map, void *key);
// int isInMap(Map *map, void *key);
long map_size(Map *map);
void free_map(Map *map);

#endif
