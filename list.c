#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

struct node {
    void *data;
    struct node *prev;
    struct node *next;
};

static struct node *get_node(struct list *list, unsigned int index);
static void *remove_node(struct list *list, struct node *node);
static struct node *merge_sort(struct node *node, bool (*compare)(void *first, void *second));
static struct node *get_middle(struct node *node);
static struct node *merge(struct node *first, struct node *second, bool (*compare)(void *first, void *second));

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

void *list_get(struct list *list, unsigned int index)
{
    struct node *node = get_node(list, index);
    if (node == NULL) {
        return NULL;
    }
    return node->data;
}

void *list_find(struct list *list, bool (*compare)(void *data, void *arg), void *arg)
{
    for (struct node* node = list->begin; node != NULL; node = node->next) {
        if (compare(node->data, arg)) {
            return node->data;
        }
    }
    return NULL;
}

void *list_remove(struct list *list, unsigned int index)
{
    struct node *node = get_node(list, index);
    if (node == NULL) {
        return NULL;
    }
    return remove_node(list, node);
}

void *list_find_and_remove(struct list *list, bool (*compare)(void *data, void *arg), void *arg)
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

void list_sort(struct list *list, bool (*compare)(void *first, void *second))
{
    if (list->size == 0) {
        return;
    }

    list->begin = merge_sort(list->begin, compare);

    for (struct node *node = list->begin; node != NULL; node = node->next) {
        list->end = node;
    }
}

static struct node *merge_sort(struct node *first, bool (*compare)(void *first, void *second))
{
    if (first->next == NULL) {
        return first;
    }

    struct node *middle = get_middle(first);
    struct node *second = middle->next;
    middle->next = NULL;

    struct node *left = merge_sort(first, compare);
    struct node *right = merge_sort(second, compare);

    return merge(left, right, compare);
}

static struct node *merge(struct node *first, struct node *second, bool (*compare)(void *first, void *second))
{
    struct node dummy;
    struct node *curr = &dummy;

    while (first != NULL) {
        while (second != NULL) {
            if (compare(first->data, second->data)) {
                curr->next = second;
                second->prev = curr;
                curr = second;
            }
            else {
                break;
            }
            second = second->next;
        }
        curr->next = first;
        first->prev = curr;
        curr = first;
        first = first->next;
    }
    if (second != NULL) {
        curr->next = second;
        second->prev = curr;
    }

    return dummy.next;
}

static struct node *get_middle(struct node *node) {
    struct node *i = node;
    struct node *j = node;

    while (j->next != NULL && j->next->next != NULL) {
        i = i->next;
        j = j->next->next;
    }

    return i;
}

static struct node *get_node(struct list *list, unsigned int index)
{
    if (list->size == 0 || index > list->size - 1) {
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
