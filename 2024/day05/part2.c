#include <stdio.h>
#include "../lib/map.h"
#include "../lib/set.h"
#include "../lib/stack.h"
#include "../lib/iterator.h"

int main(void) {
    FILE *file = fopen("input.txt", "r");
    Map *map = createMap();
    long a, b;
    while (fscanf(file, "%ld|%ld", &a, &b) == 2) {
        Set *set = mapGet(map, (void *) b);
        if (set == NULL) {
            set = createSet(NULL);
            mapSet(map, (void *) b, set);
        }
        setAdd(set, (void *) a);
    };
    fseek(file, -2, SEEK_CUR);
    int res = 0;
    while (!feof(file)) {
        Set *set = createSet(NULL);
        Set *updates = createSet(NULL);
        int correct = 1;
        do {
            fscanf(file, "%ld", &a);
            setAdd(updates, (void *) a);
            if (isInSet(set, (void *) a)) {
                correct = 0;
            }
            addSet(set, mapGet(map, (void *) a));
        } while (fgetc(file) != '\n' && !feof(file));
        freeSet(set);
        if (correct) {
            freeSet(updates);
            continue;
        }
        long n;
        for (int i = (setSize(updates) + 1) / 2; i > 0; i--) {
            Iterator *iter = iterate((Iterable *) updates);
            while (hasNext(iter)) {
                n = (long) next(iter);
                set = mapGet(map, (void *) n);
                if (set == NULL) {
                    setRemove(updates, (void *) n);
                    break;
                }
                int valid = 1;
                Iterator *iter2 = iterate((Iterable *) set);
                while (valid && hasNext(iter2)) {
                    void *x = next(iter2);
                    valid = !isInSet(updates, x);
                }
                freeIterator(iter2);
                if (valid == 1) {
                    setRemove(updates, (void *) n);
                    break;
                }
            }
            freeIterator(iter);
        }
        freeSet(updates);
        res += n;
    }
    printf("%d\n", res);
}
