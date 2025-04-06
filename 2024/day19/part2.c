#include <stdio.h>
#include <string.h>
#include "../lib/linkedList.h"
#include "../lib/stack.h"
#include "../lib/iterator.h"
#include "../lib/set.h"

int main(void) {
    FILE *file = fopen("input.txt", "r");
    fseek(file, 0, SEEK_END);
    char arr[ftell(file) + 1];
    fseek(file, 0, SEEK_SET);
    fread(arr, sizeof(char), sizeof(arr), file);
    arr[sizeof(arr) / sizeof(char) - 1] = '\0';
    strtok(arr, "\n");
    char *patterns = strtok(NULL, "") + 1;
    LinkedList *towels = createLinkedList();
    char *towel = strtok(arr, ", ");
    while (towel != NULL) {
        append(towels, towel);
        towel = strtok(NULL, ", ");
    }
    char *pattern = strtok(patterns, "\n");
    long res = 0;
    while (pattern != NULL) {
        long n[strlen(pattern) + 1];
        memset(n, 0, sizeof(n));
        n[0] = 1;
        long *np = n;
        while (*pattern != '\0') {
            Iterator *iter = iterate((Iterable *) towels);
            while (hasNext(iter)) {
                towel = next(iter);
                char *newp = pattern;
                long *newnp = np;
                while (*towel != '\0') {
                    if (*towel != *newp) {
                        break;
                    }
                    towel++;
                    newp++;
                    newnp++;
                }
                if (*towel == '\0') {
                    (*newnp) += *np;
                }
            }
            pattern++;
            np++;
        }
        res += n[sizeof(n) / sizeof(long) - 1];
        pattern = strtok(NULL, "\n");
    }
    printf("%ld\n", res);
}