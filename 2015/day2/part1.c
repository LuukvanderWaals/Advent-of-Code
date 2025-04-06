#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    int res = 0;
    char str[10];
    while (!feof(file)) {
        fgets(str, 10, file);
        char *token = strtok(str, "x");
        int dims[3];
        for (size_t i = 0; i < 3; i++) {
            int n = atol(token);
            if (n < dims[0]) {
                dims[i] = n;
            } else {
                dims[i] = dims[0];
                dims[0] = n;
            }
            token = strtok(NULL, "x");
        }
        res += 2 * (dims[0] * dims[1] + dims[0] * dims[2]) + 3 * dims[1] * dims[2];
    }
    printf("%d\n", res);
}
