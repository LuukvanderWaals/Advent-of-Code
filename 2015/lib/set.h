#ifndef SET_H
#define SET_H

#define SET_SUCCESS 0
#define SET_FAILURE 1
#define SET_ALREADY_EXISTS 2

typedef struct Set Set;

Set *create_set();
int set_add(Set *set, void *data);
void *set_remove(Set *set, void *data);
int in_set(Set *set, void *data);
int set_size(Set *set);
void print_set(Set *set, const char *format);

#endif
