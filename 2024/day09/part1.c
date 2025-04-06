#include <stdio.h>
#include "../lib/linkedList.h"

int main(void) {
    FILE *file = fopen("input.txt", "r");
    int free = 0;
    long id = 0;
    LinkedList *files = createLinkedList();
    LinkedList *space = createLinkedList();
    while (1) {
        long n = fgetc(file) - '0';
        if (feof(file)) {
            break;
        }
        append(space, (void *) n);
        if (!free) {
            for (int i = 0; i < n; i++) {
                append(files, (void *) id);
            }
            id++;
        }
        free ^= 1;
    }
    free = 0;
    long res = 0, pos = 0;
    while (linkedListSize(files) != 0) {
        long n = (long) delete(space, 0);
        for (int i = 0; i < n; i++) {
            if (!free) {
                res += pos * (long) delete(files, 0);
            } else {
                res += pos * (long) delete(files, -1);
            }
            pos++;
        }
        free ^= 1;
    }
    printf("%ld\n", res);
}
