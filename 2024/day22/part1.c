#include <stdio.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    long n;
    long sum = 0;
    while (fscanf(file, "%ld", &n) != -1) {
        for (int i = 0; i < 2000; i++) {
            n = n ^ (n << 6) & ((1 << 24) - 1);
            n = n ^ (n >> 5) & ((1 << 24) - 1);
            n = n ^ (n << 11) & ((1 << 24) - 1);
        }
        sum += n;
    }
    printf("%ld\n", sum);
}
