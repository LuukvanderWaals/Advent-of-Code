#include <stdio.h>
#include <string.h>

char directions[] = {'^', '<', '>', 'v'};

int main(void) {
    FILE *file = fopen("input.txt", "r");
    fseek(file, 0, SEEK_END);
    char arr[ftell(file) + 1];
    rewind(file);
    fread(arr, sizeof(char), sizeof(arr) - 1, file);
    fclose(file);
    arr[sizeof(arr) - 1] = '\0';
    int width = strstr(arr, "\n") - arr + 1;
    int pos = strstr(arr, "@") - arr;
    arr[pos] = '.';
    char *move = strstr(arr, "\n\n") + 1;
    int height = (move - arr) / width;
    int delta[] = {-width, -1, 1, width};
    while (1) {
        char c = *++move;
        if (c == '\n') { continue; }
        if (c == '\0') { break; }
        int d;
        for (int i = 0; i < 4; i++) {
            if (c == directions[i]) {
                d = delta[i];
                break;
            }
        }
        int push = pos;
        do {
            push += d;
        } while (arr[push] == 'O');
        if (arr[push] == '#') {
            continue;
        }
        pos += d;
        arr[push] = arr[pos];
        arr[pos] = '.';
    }
    int res = 0;
    for (int x = 0; x < width - 2; x++) {
        for (int y = 1; y < height - 1; y++) {
            if (arr[x + y * width] == 'O') {
                res += x + y * 100;
            }
        }
    }
    printf("%d\n", res);
}
