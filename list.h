#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

struct list {
    struct node *begin;
    struct node *end;
    int size;
};

void list_init(struct list *list);
void list_add(struct list *list, void *element);
void *list_get(struct list *list, int index);
void *list_find(struct list *list, bool (*compare)(void *data, char *arg), char *arg);
void *list_remove(struct list *list, int index);
void *list_find_and_remove(struct list *list, bool (*compare)(void *data, char *arg), char *arg);
void list_each(struct list *list, void (*function)(void *data));
void list_free(struct list *list);

#endif
