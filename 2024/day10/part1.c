#include <stdio.h>
#include <stdlib.h>
#include "../lib/linkedList.h"
#include "../lib/set.h"

int main(void) {
    FILE *file = fopen("input.txt", "r");
    int width = 0;
    while (fgetc(file) != '\n') {
        width++;
    }
    fseek(file, 0, SEEK_END);
    int height = (ftell(file) + 1) / (width + 1);
    fseek(file, 0, SEEK_SET);

    int map[width * height];
    Set **sets = calloc(width * height, sizeof(Set *));
    LinkedList *queue = createLinkedList();
    int d[] = {-width, -1, 1, width};

    long i = 0;
    while (1) {
        char c = fgetc(file);
        if (feof(file)) {
            break;
        }
        if (c == '\n') {
            continue;
        }
        if (c == '0') {
            append(queue, (void *) i);
            sets[i] = createSet(NULL);
            setAdd(sets[i], (void *) i);
        }
        map[i] = c - '0';
        i++;
    }
    fclose(file);

    long res = 0;
    while (linkedListSize(queue)) {
        long n = (long) delete(queue, 0);
        if (map[n] == 9) {
            res += setSize(sets[n]);
            freeSet(sets[n]);
            continue;
        }
        for (int i = 0; i < 4; i++) {
            long index = n + d[i];
            if (index >= 0 && index < width * height && map[index] == map[n] + 1) {
                if (i == 1 && n % width == 0 ||
                    i == 2 && n % width == width - 1) {
                    continue;
                }
                if (sets[index] == NULL) {
                    append(queue, (void *) index);
                    sets[index] = createSet(NULL);
                }
                addSet(sets[index], sets[n]);
            }
        }
        freeSet(sets[n]);
    }
    printf("%ld\n", res);
    free(sets);
    freeLinkedList(queue);
}
