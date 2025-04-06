#include <stdio.h>
#include <stdlib.h>

void main() {
    FILE *file = fopen("Day1.txt", "r");
    char line[255];

    int depth[4];
    for (size_t i = 0; i < 3; i++) {
        depth[i] = atoi(fgets(line, 255, file));
    }

    int res = 0;
    while (fgets(line, 255, file)) {
        depth[3] = atoi(line);
        if (depth[3] > depth[0]) {
            res++;
        }
        for (size_t i = 0; i < 4; i++) {
            printf("%d ", depth[i]);
        }
        printf("\n");
        for (size_t i = 0; i < 3; i++) {
            depth[i] = depth[i + 1];
        }
    }
    printf("%d\n", res);
}
