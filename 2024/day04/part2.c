#include "../lib/stack.h"
#include <stdio.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    while(fgetc(file) != '\n') {};
    int width = ftell(file) - 1;
    fseek(file, 0, SEEK_END);
    int height = ftell(file) / (width + 1);
    rewind(file);

    char array[width * height + 1];

    for (int i = 0; i < height; i++) {
        fgets(array + i * width, width + 1, file);
        fseek(file, 1, SEEK_CUR);
    }

    int res = 0;

    for (int x = 1; x < width - 1; x++) {
        for (int y = 1; y < height - 1; y++) {
            int i = x + y * width;
            if (
                array[i] == 'A' && (
                    (
                        (array[i - width - 1] == 'M' && array[i + width + 1] == 'S') ||
                        (array[i - width - 1] == 'S' && array[i + width + 1] == 'M')
                    ) && (
                        (array[i - width + 1] == 'M' && array[i + width - 1] == 'S') ||
                        (array[i - width + 1] == 'S' && array[i + width - 1] == 'M')
                    )
                )
            ) {
                res++;
            }
        }
    }

    printf("%d\n", res);

    fclose(file);
}
