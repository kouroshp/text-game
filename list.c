#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_init(struct list* list)
{
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;
}

void list_add(struct list* list, void* element)
{
    struct node* node = malloc(sizeof(struct node));
    node->data = element;
    node->next = NULL;

    // If list is empty, set the begin to new node
    if (list->size == 0) {
        list->begin = node;
    }
    else {
        struct node* last = list->end;
        last->next = node;
    }

    list->size += 1;
    list->end = node;
}

struct node* list_get(struct list* list, int index)
{
    if (list->size == 0 || index < 0 || index > list->size - 1) {
        return NULL;
    }

    // If requesting last node, just return it
    if (index == list->size - 1) {
        return list->end;
    }

    struct node* node = list->begin;

    for (int i = 0; i < index; i++) {
        node = node->next;
    }

    return node;
}

void list_remove(struct list* list, int index)
{
    struct node* curr;
    struct node* prev;

    if (list->size == 0 || index < 0 || index > list->size - 1) {
        return;
    }

    if (index == 0) {
        curr = list->begin;
        if (curr->next != NULL) {
            list->begin = curr->next;
        }
    }
    else {
        // Get node prior to one to remove
        prev = list_get(list, index - 1);
        curr = prev->next;

        // Update links
        if (curr == list->end) {
            prev->next = NULL;
            list->end = prev;
        }
        else {
            struct node* next = curr->next;
            prev->next = next;
        }
    }

    // Remove node
    free(curr);
    list->size -= 1;
}

void list_each(struct list* list, void (*function)(void* data))
{
    struct node* node = list->begin;

    for (int i = 0; i < list->size; i++) {
        function(node->data);
        node = node->next;
    }
}

void list_free(struct list* list)
{
    if (list->size == 0) {
        return;
    }
    else {
        struct node* curr = list->begin;
        struct node* next;

        for (int i = 0; i < list->size - 1; i++) {
            next = curr->next;
            free(curr->data);
            free(curr);
            curr = next;
        }
        free(curr->data);
        free(curr);
    }
}
