// #include <stdlib.h>
// #include <stdio.h>
// #include "dynamicString.h"

// struct DynamicString {
//     int len;
//     int size;
//     char *data;
// };

// DynamicString *createDynamicString(int len) {
//     if (len <= 0) {
//         return (DynamicString *) calloc(1, sizeof(DynamicString));
//     }
//     DynamicString *ds = malloc(sizeof(DynamicString));
//     ds->len = len;
//     ds->size = len + 1;
//     ds->data = calloc(ds->size, sizeof(char));
//     return ds;
// }

// DynamicString *readLine(DynamicString *ds, FILE *f) {
//     printf("Test");
// }
