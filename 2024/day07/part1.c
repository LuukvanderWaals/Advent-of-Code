#include <stdio.h>
#include "../lib/set.h"
#include "../lib/iterator.h"

int main(void) {
    FILE *file = fopen("input.txt", "r");
    long n, x, res = 0;
    while (!feof(file)) {
        fscanf(file, "%ld: %ld", &n, &x);
        Set *a = createSet(NULL);
        setAdd(a, (void *) x);
        while (fgetc(file) == ' ' && !feof(file)) {
            fscanf(file, "%ld", &x);
            Set *b = createSet(NULL);
            Iterator *iter = iterate((Iterable *) a);
            while (hasNext(iter)) {
                long y = (long) next(iter);
                long r = x + y;
                if (r <= n) {
                    setAdd(b, (void *) r);
                }
                r = x * y;
                if (r <= n) {
                    setAdd(b, (void *) r);
                }
            }
            freeIterator(iter);
            freeSet(a);
            a = b;
        }
        if (isInSet(a, (void *) n)) {
            res += n;
        }
        freeSet(a);
    }
    fclose(file);
    printf("%ld\n", res);
}
