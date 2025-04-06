#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/set.h"

// void toggle(int x1, int y1, int x2, int y2, Set *set) {
//     for (int x = x1; x <= x2; x++) {
//         for (int y = y1; y < y2; y++) {
//             void *c = (long) x * 1000 + y;
//             if (set_add(set, c) == SET_ALREADY_EXISTS) {
//                 set_remove(set, c);
//             };
//         }
//     }
//     printf("%d\n", set_size(set));
// }

int main(void) {
    FILE *file = fopen("input.txt", "r");
    char s[34];
    Set *set = create_set(NULL);
    set_add(set, (void *)1);
    set_add(set, (void *)2);
    set_add(set, (void *)3);
    set_add(set, (void *)0);
    printf("%d\n", set_remove(set, (void *)3));
    // while (fgets(s, 34, file)) {
    //     char *instr = strtok(s, " ");
    //     if (!strcmp(s, "turn")) {
    //         instr = strtok(NULL, " ");
    //     }
    //     int x1 = atoi(strtok(NULL, ","));
    //     int y1 = atoi(strtok(NULL, " "));
    //     int x2;
    //     int y2;
    //     strtok(NULL, " ");
    //     int x;
    //     if ((x = atoi(strtok(NULL, ","))) < x1) {
    //         x2 = x1;
    //         x1 = x;
    //     } else {
    //         x2 = x;
    //     }
    //     int y;
    //     if ((y = atoi(strtok(NULL, ","))) < y1) {
    //         y2 = y1;
    //         y1 = y;
    //     } else {
    //         y2 = y;
    //     }
    //     if (!strcmp(instr, "toggle")) {
    //         toggle(x1, y1, x2, y2, set);
    //     } else if (!strcmp(instr, "on")) {
    //         // on(a, b);
    //     } else {
    //         // off(a, b);
    //     }
    // }
}
