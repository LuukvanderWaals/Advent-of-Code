#include <stdio.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    int x, y, res = 0;
    while (!feof(file)) {
        if (fscanf(file, "mul(%d,%d", &x, &y) == 2) {
            if (fgetc(file) == ')') {
                res += x * y;
            }
            continue;
        };
        fgetc(file);
    }
    printf("%d\n", res);
    fclose(file);
}
