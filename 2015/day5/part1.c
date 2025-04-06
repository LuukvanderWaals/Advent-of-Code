#include <stdio.h>
#include <string.h>

const char *vowels = "aeiou";
const char *naughty_strings[] = {"ab", "cd", "pq", "xy"};

int main(void) {
    FILE *file = fopen("input.txt", "r");
    char s[18];
    int nice_strings = 0;
    while (fgets(s, 18, file)) {
        int nice = 0;
        int n_vowels = 0;
        for (int i = 0; i < 16; i++) {
            n_vowels += strchr(vowels, s[i]) != NULL;
            if (strstr(s, vowels) != NULL) {
                n_vowels++;
            }
            if (s[i] == s[i + 1]) {
                nice = 1;
            }
        }
        if (nice == 0 || n_vowels < 3) {
            continue;
        }
        nice = 1;
        for (int i = 0; i < 4; i++) {
            if (strstr(s, naughty_strings[i]) != NULL) {
                nice = 0;
                break;
            }
        }
        if (nice == 0) {
            continue;
        }
        nice_strings++;
    }
    printf("%d\n", nice_strings);
}
