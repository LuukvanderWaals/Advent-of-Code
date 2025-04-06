#include <stdio.h>
#include "../lib/map.h"
#include "../lib/set.h"
#include "../lib/stack.h"

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
        Stack *stack = createStack();
        int correct = 1;
        do {
            fscanf(file, "%ld", &a);
            push(stack, (void *) a);
            if (isInSet(set, (void *) a)) {
                correct = 0;
            }
            addSet(set, mapGet(map, (void *) a));
        } while (fgetc(file) != '\n' && !feof(file));
        if (correct) {
            for (int i = (size(stack) - 1) / 2; i > 0; i--) {
                pop(stack);
            }
            res += (long) pop(stack);
        }
        freeSet(set);
        freeStack(stack);
    }
    printf("%d\n", res);
}
