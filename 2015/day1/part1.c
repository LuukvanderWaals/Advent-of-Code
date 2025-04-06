#include <stdio.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    char c;
    int res = 0;
    while ((c = fgetc(file)) != EOF) {
        res += c == '(' ? 1 : -1;
    }
    printf("%d\n", res);
}
