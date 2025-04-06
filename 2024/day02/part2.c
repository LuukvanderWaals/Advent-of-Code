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
        int bad = 0;
        if (x == y || abs(x - y) > 3) {
            bad = 1;
        }
        int dir = x < y ? 1 : -1;
        while (fgetc(file) != 10 && !feof(file)) {
            x = y;
            fscanf(file, "%d", &y);
            int d = (y - x) * dir;
            if (d <= 0 || d > 3) {
                bad++;
            }
        }
        if (bad < 2) {
            res++;
        }
    }
    printf("%d\n", res);
    fclose(file);
}
