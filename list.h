#ifndef LIST_H
#define LIST_H

struct node {
    void* data;
    struct node* next;
};

struct list {
    struct node* begin;
    struct node* end;
    int size;
};

void list_init(struct list* list);
void list_add(struct list* list, void* element);
struct node* list_get(struct list* list, int index);
void list_remove(struct list* list, int index);
void list_each(struct list* list, void (*function)(void* data));
void list_free(struct list* list);

#endif
