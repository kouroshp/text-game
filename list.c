#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

struct node {
    void *data;
    struct node *prev;
    struct node *next;
};

static struct node *get_node(struct list *list, int index);
static void *remove_node(struct list *list, struct node *node);

void list_init(struct list *list)
{
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;
}

void list_add(struct list *list, void *element)
{
    struct node *node = malloc(sizeof(*node));
    node->data = element;
    node->prev = NULL;
    node->next = NULL;

    // If list is empty, set the begin to new node
    if (list->size == 0) {
        list->begin = node;
    }
    else {
        struct node *last = list->end;
        last->next = node;
        node->prev = last;
    }

    list->size += 1;
    list->end = node;
}

void *list_get(struct list *list, int index)
{
    struct node *node = get_node(list, index);
    if (node == NULL) {
        return NULL;
    }
    return node->data;
}

void *list_find(struct list *list, bool (*compare)(void *data, char *arg), char *arg)
{
    for (struct node* node = list->begin; node != NULL; node = node->next) {
        if (compare(node->data, arg)) {
            return node->data;
        }
    }
    return NULL;
}

void *list_remove(struct list *list, int index)
{
    struct node *node = get_node(list, index);
    if (node == NULL) {
        return NULL;
    }
    return remove_node(list, node);
}

void *list_find_and_remove(struct list *list, bool (*compare)(void *data, char *arg), char *arg)
{
    for (struct node* node = list->begin; node != NULL; node = node->next) {
        if (compare(node->data, arg)) {
            return remove_node(list, node);
        }
    }
    return NULL;
}

void list_each(struct list *list, void (*function)(void *data))
{
    for (struct node *node = list->begin; node != NULL; node = node->next) {
        function(node->data);
    }
}

void list_free(struct list *list)
{
    if (list->size == 0) {
        return;
    }
    else {
        struct node *curr, *next;

        for (curr = list->begin; curr != NULL; curr = next) {
            next = curr->next;
            free(curr);
        }
    }
}

static struct node *get_node(struct list *list, int index)
{
    if (list->size == 0 || index < 0 || index > list->size - 1) {
        return NULL;
    }

    // If requesting last node, just return it
    if (index == list->size - 1) {
        return list->end;
    }

    struct node *node = list->begin;

    for (int i = 0; i < index; i++) {
        node = node->next;
    }

    return node;
}

static void *remove_node(struct list *list, struct node *node)
{
    if (node == list->begin) {
        if (node->next != NULL) {
            list->begin = node->next;
            list->begin->prev = NULL;
        }
        else {
            // Nothing left in the list
            list->begin = NULL;
            list->end = NULL;
        }
    }
    else {
        // Update links
        if (node == list->end) {
            list->end = node->prev;
            list->end->next = NULL;
        }
        else {
            struct node *prev = node->prev;
            struct node *next = node->next;
            prev->next = next;
            next->prev = prev;
        }
    }

    // Remove node
    void *data = node->data;
    free(node);
    list->size -= 1;
    return data;
}
