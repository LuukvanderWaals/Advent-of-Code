#include <stdio.h>
#include "../lib/set.h"
#include "../lib/iterator.h"
#include "../lib/stack.h"

long setPos(int x, int y) {
    return ((long) x << sizeof(int) * 8) + y;
}

void getPos(long pos, int *x, int *y) {
    *x = pos >> sizeof(int) * 8;
    *y = (int) pos;
}

long main(void) {
    FILE *file = fopen("input.txt", "r");
    while (fgetc(file) != '\n') {}
    int width = ftell(file) - 1;
    fseek(file, 0, SEEK_END);
    int height = (ftell(file) + 1) / (width + 1);
    rewind(file);
    char arr[width * height];

    for (int i = 0; i < height; i++) {
        fgets(arr + i * width, width + 1, file);
        fseek(file, 1, SEEK_CUR);
    }
    fclose(file);
    int price = 0;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    Set *visited = createSet(NULL);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            long pos = setPos(x, y);
            if (isInSet(visited, (void *) pos)) {
                continue;
            }
            char c = arr[x + y * width];
            int x, y;
            int perimeter = 0, area = 1;
            setAdd(visited, (void *) pos);
            Stack *stack = createStack();
            push(stack, (void *) pos);
            while (!isEmpty(stack)) {
                getPos((long) pop(stack), &x, &y);
                for (long i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx < 0 || nx >= width || ny < 0 || ny >= height || arr[nx + (ny) * width] != c) {
                        perimeter++;
                        continue;
                    }
                    pos = setPos(nx, ny);
                    if (!isInSet(visited, (void *) pos)) {
                        area++;
                        setAdd(visited, (void *) pos);
                        push(stack, (void *) pos);
                    }
                }
            }
            freeStack(stack);
            price += area * perimeter;
        }
    }
    printf("%d\n", price);
    freeSet(visited);
}
