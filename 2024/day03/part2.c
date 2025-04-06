#include <stdio.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    int x, y, res = 0, enabled = 1;
    char *d = "do()";
    char *dop = d;
    char *dont = "don't()";
    char *dontp = dont;
    while (1) {
        char c = fgetc(file);
        if (feof(file)) {
            break;
        }
        if (c == *dop) {
            dop++;
            if (*dop == '\0') {
                enabled = 1;
                dop = d;
            }
        } else {
            dop = d;
        }
        if (c == *dontp) {
            dontp++;
            if (*dontp == '\0') {
                enabled = 0;
                dontp = dont;
            }
        } else {
            dontp = dont;
        }
        fseek(file, -1, SEEK_CUR);
        if (fscanf(file, "mul(%d,%d", &x, &y) == 2) {
            if (fgetc(file) == ')') {
                res += enabled * x * y;
            }
            continue;
        };
        fseek(file, 1, SEEK_CUR);
    }
    printf("%d\n", res);
    fclose(file);
}
