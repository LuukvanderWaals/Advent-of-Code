#include <stdio.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    int ax, ay, bx, by, px, py;
    int tokens = 0;
    while (fscanf(file, "Button A: X+%d, Y+%d\n", &ax, &ay) != -1) {
        fscanf(file, "Button B: X+%d, Y+%d\n", &bx, &by);
        fscanf(file, "Prize: X=%d, Y=%d\n", &px, &py);
        int pt = (px * by - py * bx);
        int at = (ax * by - ay * bx);
        if (pt % at == 0) {
            int a = pt / at;
            int b = (px - a * ax) / bx;
            tokens += a * 3 + b;
        }
    }
    printf("%d\n", tokens);
}
