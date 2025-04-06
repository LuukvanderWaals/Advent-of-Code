#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    FILE *file = fopen("Day2.txt", "r");
    char line[255];

    int aim = 0, depth = 0, x = 0;
    while (fgets(line, 255, file)) {
        char *direction = strtok(line, " ");
        int n = atoi(strtok(NULL, ""));

        if (strcmp(direction, "forward") == 0) {
            x += n;
            depth += n * aim;
        } else if (strcmp(direction, "up") == 0) {
            aim -= n;
        } else if (strcmp(direction, "down") == 0) {
            aim += n;
        }
    }
    printf("%d\n", x * depth);
}