#include <stdio.h>
#include <string.h>
#include "../lib/linkedList.h"
#include "../lib/iterator.h"

int main(void) {
    FILE *file = fopen("input.txt", "r");
    char buffer[7];
    LinkedList *locks = createLinkedList();
    LinkedList *keys = createLinkedList();
    while (!feof(file)) {
        fgets(buffer, 7, file);
        char c = *buffer;
        char heights[8] = {-1, -1, -1, -1, -1};
        for (int i = 0; !feof(file); i++) {
            fgets(buffer, 7, file);
            if (strlen(buffer) <= 1) {
                break;
            }
            for (int j = 0; j < 5; j++) {
                if (heights[j] == -1 && buffer[j] != c) {
                    heights[j] = i;
                }
            }
        }
        append(c == '#' ? locks : keys, *(void **) heights);
    }
    int res = 0;
    Iterator *iterLocks = iterate((Iterable *) locks);
    while (hasNext(iterLocks)) {
        void *l = next(iterLocks);
        char *lock = (char *) &l;
        Iterator *iterKeys = iterate((Iterable *) keys);
        while (hasNext(iterKeys)) {
            void *k = next(iterKeys);
            char *key = (char *) &k;
            int check = 0;
            for (int i = 0; i < 5; i++) {
                check += lock[i] > key[i];
            }
            res += check == 0;
        }
    }
    printf("%d\n", res);
}
