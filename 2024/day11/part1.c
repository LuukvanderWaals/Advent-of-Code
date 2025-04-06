#include "../lib/map.h"
#include "../lib/iterator.h"
#include <stdio.h>
#include <math.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    Map *map = create_map(NULL);
    long x;
    while (fscanf(file, "%ld", &x) !=- 1) {
        map_set(map, (void *) x, (void *) 1);
    }
    for (int i = 0; i < 25; i++) {
        Iterator *iter = iterate(map);
        Map *newMap = create_map(NULL);
        while(hasNext(iter)) {
            long key = (long) next(iter);
            long value = (long) map_get(map, (void *) key);
            if (key == 0) {
                map_set(newMap, (void *) 1, map_get(newMap, (void *) 1) + value);
                continue;
            }
            long t = 10;
            int even = 0;
            int p = 1;
            while (t <= key) {
                t *= 10;
                if (even == 1) {
                    p++;
                }
                even ^= 1;
            }
            if (even) {
                t = pow(10, p);
                map_set(newMap, (void *) (key / t), map_get(newMap, (void *) (key / t)) + value);
                map_set(newMap, (void *) (key % t), map_get(newMap, (void *) (key % t)) + value);
            } else {
                map_set(newMap, (void *) (key * 2024), map_get(newMap, (void *) (key * 2024)) + value);
            }
        }
        freeIterator(iter);
        free_map(map);
        map = newMap;
    }
    Iterator *iter = iterate(map);
    long stones = 0;
    while (hasNext(iter)) {
        stones += (long) map_get(map, next(iter));
    }
    freeIterator(iter);
    printf("%ld\n", stones);
    printf("%ld\n", map_size(map));
}
