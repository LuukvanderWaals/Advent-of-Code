#include <stdio.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    long ax, ay, bx, by, px, py;
    long tokens = 0;
    while (fscanf(file, "Button A: X+%ld, Y+%ld\n", &ax, &ay) != -1) {
        fscanf(file, "Button B: X+%ld, Y+%ld\n", &bx, &by);
        fscanf(file, "Prize: X=%ld, Y=%ld\n", &px, &py);
        px += 10000000000000;
        py += 10000000000000;
        long pt = (px * by - py * bx);
        long at = (ax * by - ay * bx);
        printf("%ld, %ld\n", pt, at);
        if (pt % at == 0) {
            long a = pt / at;
            long bt = px - a * ax;
            if (bt % bx != 0) {
                continue;
            }
            long b = bt / bx;
            tokens += a * 3 + b;
        }
    }
    printf("%ld\n", tokens);
}
