#include <stdio.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    // int width = 11, height = 7;
    int width = 101, height = 103;
    int x, y, vx, vy;
    int quadrant[] = {0, 0, 0, 0};
    while (fscanf(file, "p=%d,%d v=%d,%d\n", &x, &y, &vx, &vy) != -1) {
        x = (x + 100 * (vx + width)) % width;
        y = (y + 100 * (vy + height)) % height;
        int q = 0;
        if (x == width / 2) {
            continue;
        }
        if (y == height / 2) {
            continue;
        }
        if (x > width / 2) {
            q++;
        }
        if (y > height / 2) {
            q += 2;
        }
        quadrant[q]++;
    }
    int safety = 1;
    for (int i = 0; i < 4; i++) {
        safety *= quadrant[i];
    }
    printf("%d\n", safety);
}
