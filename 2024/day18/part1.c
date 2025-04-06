#include <stdio.h>
#include <string.h>
#include "../lib/linkedList.h"

int main(void) {
    FILE *file = fopen("input.txt", "r");
    int width = 71, height = 71;
    int size = (width + 1) * (height + 2);
    int arr[size];
    memset(arr, 0, sizeof(arr));
    int end = size - width - 2;
    printf("End: %d\n", end);
    for (int i = 0; i < width + 1; i++) {
        arr[i] = -1;
        arr[size - i - 1] = -1;
    }
    for (int i = 1; i < height + 1; i++) {
        arr[i * (width + 1)] = -1;
    }
    int x, y;
    for (int i = 0; i < 1024; i++) {
        fscanf(file, "%d,%d", &x, &y);
        arr[(y + 1) * (width + 1) + x + 1] = -1;
    }
    int delta[] = {-width - 1, -1, 1, width + 1};
    LinkedList *queue = createLinkedList();
    append(queue, (void *) (width + 2L));
    while (linkedListSize(queue) != 0) {
        long pos = (long) delete(queue, 0);
        if (pos == end) {
            printf("%d\n", arr[pos]);
            break;
        }
        int dist = arr[pos] + 1;
        for (int i = 0; i < 4; i++) {
            long newPos = pos + delta[i];
            if (arr[newPos] == 0 || arr[newPos] > dist) {
                arr[newPos] = dist;
                append(queue, (void *) newPos);
            }
        }
    }
}
