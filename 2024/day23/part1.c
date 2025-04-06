#include <stdio.h>
#include "../lib/map.h"
#include "../lib/set.h"
#include "../lib/iterator.h"

int main(void) {
    FILE *file = fopen("input.txt", "r");
    char a[sizeof(long) / sizeof(char)] = {0}, b[sizeof(long) / sizeof(char)] = {0};
    Map *map = createMap(NULL);
    int res = 0;
    while (fscanf(file, "%2s-%2s", a, b) != -1) {
        Set *seta = mapGet(map, (void *) *((long *) a));
        if (seta == NULL) {
            seta = createSet(NULL);
            mapSet(map, (void *) *((long *) a), seta);
        }
        setAdd(seta, (void *) *((long *) b));

        Set *setb = mapGet(map, (void *) *((long *) b));
        if (setb == NULL) {
            setb = createSet(NULL);
            mapSet(map, (void *) *((long *) b), setb);
        }
        setAdd(setb, (void *) *((long *) a));

        Iterator *iter = iterate((Iterable *) seta);
        while (hasNext(iter)) {
            void *c = next(iter);
            if ((*(char *) a == 't' || *(char *) b == 't' || *(char *) &c == 't') && isInSet(setb, c)) {
                res++;
            }
        }
    }
    printf("%d\n", res);
}
