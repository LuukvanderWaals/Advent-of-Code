#include "../lib/stack.h"
#include <stdio.h>

char *xmas, *xmasp, *samx, *samxp;
int res;

void check(char *array, int index) {
    if (array[index] == *xmasp) {
        xmasp++;
        if (*xmasp == '\0') {
            res++;
            xmasp = xmas;
        }
    } else {
        xmasp = xmas;
        if (array[index] == *xmasp) {
            xmasp++;
        }
    }
    if (array[index] == *samxp) {
        samxp++;
        if (*samxp == '\0') {
            res++;
            samxp = samx;
        }
    } else {
        samxp = samx;
        if (array[index] == *samxp) {
            samxp++;
        }
    }
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    while(fgetc(file) != '\n') {};
    int width = ftell(file) - 1;
    fseek(file, 0, SEEK_END);
    int height = ftell(file) / (width + 1);
    rewind(file);

    xmas = "XMAS";
    xmasp = xmas;
    samx = "SAMX";
    samxp = samx;
    char array[width * height + 1];

    for (int i = 0; i < height; i++) {
        fgets(array + i * width, width + 1, file);
        fseek(file, 1, SEEK_CUR);
    }

    res = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            check(array, i * width + j);
        }
        xmasp = xmas;
        samxp = samx;
    }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            check(array, i + j * width);
        }
        xmasp = xmas;
        samxp = samx;
    }

    for (int i = 3 - height; i < height - 3; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width + j * (width + 1);
            if (index < 0) {
                continue;
            }
            if (index >= width * height) {
                break;
            }
            check(array, index);
        }
        xmasp = xmas;
        samxp = samx;
    }

    for (int i = 3; i < height * 2 - 3; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width - j * (width - 1);
            if (index >= width * height) {
                continue;
            }
            if (index < 0) {
                break;
            }
            check(array, index);
        }
        xmasp = xmas;
        samxp = samx;
    }

    printf("%d\n", res);

    fclose(file);
}
