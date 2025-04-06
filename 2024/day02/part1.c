#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../lib/linkedList.h"

int comp(void *a, void *b) {
    return (int) (a - b);
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    int x, y;
    int res = 0;
    int i = 0;
    while (!feof(file)) {
        i++;
        fscanf(file, "%d %d", &x, &y);
        int success = 1;
        if (x == y || abs(x - y) > 3) {
            success = 0;
        }
        int dir = x < y ? 1 : -1;
        while (fgetc(file) != 10 && !feof(file)) {
            x = y;
            fscanf(file, "%d", &y);
            int d = (y - x) * dir;
            if (success == 1 && (d <= 0 || d > 3)) {
                success = 0;
            }
        }
        res += success;
    }
    printf("%d\n", res);
    fclose(file);
}
