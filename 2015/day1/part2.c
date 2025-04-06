#include <stdio.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    char c;
    int floor = 0;
    int pos = 1;
    while ((c = fgetc(file)) != EOF) {
        floor += c == '(' ? 1 : -1;
        if (floor < 0) {
            break;
        }
        pos += 1;
    }
    printf("%d\n", pos);
}
