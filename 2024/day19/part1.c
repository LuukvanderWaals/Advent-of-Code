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
    int n = 0;
    while (pattern != NULL) {
        Stack *stack = createStack();
        Set *set = createSet(NULL);
        push(stack, pattern);
        while (!isEmpty(stack)) {
            pattern = pop(stack);
            Iterator *iter = iterate((Iterable *) towels);
            int b = 0;
            while (hasNext(iter)) {
                towel = next(iter);
                char *newp = pattern;
                while (*towel != '\0') {
                    if (*towel != *newp) {
                        break;
                    }
                    towel++;
                    newp++;
                }
                if (*towel == '\0' && !isInSet(set, newp)) {
                    if (*newp == '\0') {
                        b = 1;
                        n++;
                        break;
                    }
                    push(stack, newp);
                    setAdd(set, newp);
                }
            }
            if (b) {
                break;
            }
        }
        pattern = strtok(NULL, "\n");
    }
    printf("%d\n", n);
}