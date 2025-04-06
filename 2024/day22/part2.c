#include <stdio.h>
#include "../lib/set.h"
#include "../lib/map.h"

int main(void) {
    FILE *file = fopen("input.txt", "r");
    long n;
    long sum = 0;
    char buffer[4];
    unsigned int *bp = (int *) buffer;
    *bp >>= 8;
    int maxPrice = 0;
    Map *prices = createMap(NULL);
    while (fscanf(file, "%ld", &n) != -1) {
        for (int i = 0; i < 4; i++) {
            buffer[i] = 10;
        }
        int price = n % 10;
        Set *visited = createSet(NULL);
        for (int i = 0; i < 2000; i++) {
            n = n ^ (n << 6) & ((1 << 24) - 1);
            n = n ^ (n >> 5) & ((1 << 24) - 1);
            n = n ^ (n << 11) & ((1 << 24) - 1);
            int newPrice = n % 10;
            *bp <<= 8;
            buffer[0] = newPrice - price;
            price = newPrice;
            if (!isInSet(visited, (void *) (long) *bp) && buffer[3] != 10) {
                setAdd(visited, (void *) (long) *bp);
                long p = (long) mapGet(prices, (void *) (long) *bp) + price;
                mapSet(prices, (void *) (long) *bp, (void *) (long) p);
                if (p > maxPrice) {
                    maxPrice = p;
                }
            }
        }
        freeSet(visited);
    }
    printf("%d\n", maxPrice);
}
