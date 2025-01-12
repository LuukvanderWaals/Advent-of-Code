#ifndef MAP_H
#define MAP_H

typedef struct Map Map;

Map *createMap();
int mapSet(Map *, void *, void *);
void *mapGet(Map *, void *);
int isInMap(Map *, void *);
void freeMap(Map *);

#endif
