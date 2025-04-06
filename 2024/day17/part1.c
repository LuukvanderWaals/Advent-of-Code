#include <stdio.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    int registers[3];
    fscanf(file, "Register A: %d\n", &registers[0]);
    fscanf(file, "Register B: %d\n", &registers[1]);
    fscanf(file, "Register C: %d\n", &registers[2]);
    fseek(file, 9, SEEK_CUR);
    int start = ftell(file);
    fseek(file, 0, SEEK_END);
    int end = ftell(file);
    int size = (end - start + 1) / 2;
    int arr[size];
    fseek(file, start - end, SEEK_CUR);
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d,", arr + i);
    }
    int p = 0;
    int out = 0;
    while (p < size) {
        printf("\n%d, %d, %d\n\n", registers[0], registers[1], registers[2]);
        for (int i = 0; i < size; i += 2) {
            // printf("| %d %d ", arr[i], arr[i + 1]);
        }
        // printf("\n  ");
        for (int i = 0; i < p >> 1; i++) {
            // printf("      ");
        }
        // printf("^\n");
        int opcode = arr[p], operant = arr[p + 1];
        if (operant > 3 && operant < 7 && opcode != 1 && opcode != 3) {
            operant = registers[operant - 4];
        }
        switch (opcode) {
            case 0:
                registers[0] >>= operant;
                break;
            case 1:
                registers[1] ^= operant;
                break;
            case 2:
                registers[1] = operant & 7;
                break;
            case 3:
                if (registers[0] != 0) {
                    p = (operant - 1) * 2;
                }
                break;
            case 4:
                registers[1] ^= registers[2];
                break;
            case 5:
                if (out) {
                    printf(",");
                }
                printf("%d", operant % 8);
                out = 1;
                break;
            case 6:
                registers[1] = registers[0] >> operant;
                break;
            case 7:
                registers[2] = registers[0] >> operant;
                break;
        }
        p += 2;
        int x;
        // fgetc(stdin);
    }
    printf("\n");
    // printf("%d, %d, %d\n", registers[0], registers[1], registers[2]);
}