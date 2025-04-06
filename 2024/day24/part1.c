#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/map.h"
#include "../lib/set.h"
#include "../lib/linkedList.h"

typedef struct {
    char *a;
    char *b;
    char *c;
    int op;
} Operation;

int main(void) {
    FILE *file = fopen("input.txt", "r");
    fseek(file, 0, SEEK_END);
    char input[ftell(file) + 1];
    fseek(file, 0, SEEK_SET);
    fread(input, 1, sizeof(input) - sizeof(char), file);
    input[sizeof(input) / sizeof(char) - 1] = 0;
    char *operations = strstr(input, "\n\n");
    *operations = '\0';
    operations += 2;
    Map *map = createMap(strcmp);
    char *key = strtok(input, ":");
    while (key != NULL) {
        char *value = strtok(NULL, "\n");
        mapSet(map, key, (void *) strtol(value, NULL, 10));
        key = strtok(NULL, ":");
    }
    char *a = strtok(operations, " ");
    LinkedList *queue = createLinkedList();
    while (a != NULL) {
        Operation *operation = malloc(sizeof(Operation));
        operation->a = a;
        operation->op = strcmp(strtok(NULL, " "), "OR") & 3; // 0: OR, 1: XOR, 2: AND
        operation->b = strtok(NULL, " ");
        strtok(NULL, " ");
        operation->c = strtok(NULL, "\n");
        append(queue, operation);
        a = strtok(NULL, " ");
    }
    while (linkedListSize(queue) != 0) {
        Operation *operation = delete(queue, 0);
        if (!isInMap(map, operation->a) || !isInMap(map, operation->b)) {
            append(queue, operation);
            continue;
        }
        switch (operation->op) {
            case 0:
                mapSet(map, operation->c, (void *) ((long) mapGet(map, operation->a) | (long) mapGet(map, operation->b)));
                break;
            case 1:
                mapSet(map, operation->c, (void *) ((long) mapGet(map, operation->a) ^ (long) mapGet(map, operation->b)));
                break;
            case 2:
                mapSet(map, operation->c, (void *) ((long) mapGet(map, operation->a) & (long) mapGet(map, operation->b)));
        }
    }
    unsigned long res = 0;
    for (int i = 0; i < sizeof(res) * 8; i++) {
        res >>= 1;
        char key[4] = {0};
        sprintf(key, "z%02d", i);
        if (mapGet(map, key)) {
            res |= 1L << sizeof(res) * 8 - 1;
        }
    }
    printf("%ld\n", res);
}
