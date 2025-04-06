#include <stdio.h>
#include <string.h>
#include "../lib/set.h"

const char *vowels = "aeiou";
const char *naughty_strings[] = {"ab", "cd", "pq", "xy"};

int main(void) {
    FILE *file = fopen("input.txt", "r");
    char s[18];
    short *n;
    int nice_strings = 0;
    while (fgets(s, 18, file)) {
        n = (short *)s;
        Set *set = create_set(NULL);
        int double_pair = 0;
        int repeat = 0;
        int pair = 0;
        for (int i = 0; i < 15; i++) {
            n = (short *)(s + i);
            if (in_set(set, (void *)*n)) {
                double_pair = 1;
            }
            if (s[i] == s[i + 2]) {
                repeat = 1;
            }
            set_add(set, (void *)pair);
            pair = *n;
        }
        if (double_pair && repeat) {
            nice_strings++;
        }
    }
    printf("%d\n", nice_strings);
}
