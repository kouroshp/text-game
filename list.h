#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

struct list {
    struct node *begin;
    struct node *end;
    unsigned int size;
};

void list_init(struct list *list);
void list_add(struct list *list, void *element);
void *list_get(struct list *list, unsigned int index);
void *list_find(struct list *list, bool (*compare)(void *data, void *arg), void *arg);
void *list_remove(struct list *list, unsigned int index);
void *list_find_and_remove(struct list *list, bool (*compare)(void *data, void *arg), void *arg);
void list_each(struct list *list, void (*function)(void *data));
void list_free(struct list *list);
void list_sort(struct list *list, bool (*comparer)(void *first, void *second));

#endif
