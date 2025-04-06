#include <stdio.h>

typedef struct {
    int position;
    int size;
} Memory;

int main(void) {
    FILE *input = fopen("input.txt", "r");
    fseek(input, 0, SEEK_END);
    int n_files = (ftell(input) + 1) / 2;
    Memory files[n_files];
    Memory space[n_files - 1];
    fseek(input, 0, SEEK_SET);
    long i = 0, pos = 0, size;
    while (1) {
        size = fgetc(input) - '0';
        files[i] = (Memory) {pos, size};
        pos += size;
        size = fgetc(input) - '0';
        if (feof(input)) {
            break;
        }
        space[i] = (Memory) {pos, size};
        pos += size;
        i++;
    }
    for (int i = n_files - 1; i > 1; i--) {
        for (int j = 0; j < i; j++) {
            if (space[j].size >= files[i].size) {
                files[i].position = space[j].position;
                space[j].position += files[i].size;
                space[j].size -= files[i].size;
                break;
            }
        }
    }
    long checksum = 0;
    for (int i = 0; i < n_files; i++) {
        long pos = files[i].position;
        long size = files[i].size;
        checksum += pos * i * size + i * size * (size - 1) / 2;
    }
    printf("%ld\n", checksum);
}
