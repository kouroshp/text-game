#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "item.h"
#include "inventory.h"

static bool name_finder(void *data, void *arg);
static bool name_comparer(void *first, void *second);
static void item_print(void *data);
static void item_free(void *data);

void inventory_init(struct inventory *inventory)
{
    inventory->size = 0;
    inventory->capacity = 10;
    list_init(&inventory->contents);
}

bool inventory_add(struct inventory *inventory, struct item *item)
{
    if (inventory->size + item->weight <= inventory->capacity) {
        list_add(&inventory->contents, item);
        inventory->size += item->weight;
        return true;
    }
    return false;
}

struct item *inventory_remove(struct inventory *inventory, const char *name)
{
    struct item *item = list_find_and_remove(&inventory->contents, &name_finder, (void *)name);
    if (item == NULL) {
        return NULL;
    }

    inventory->size -= item->weight;
    return item;
}

struct item *inventory_get(struct inventory *inventory, const char *name)
{
    return list_find(&inventory->contents, &name_finder, (void *)name);
}

void inventory_contents_print(struct inventory *inventory)
{
    list_sort(&inventory->contents, &name_comparer);
    if (inventory->size == 0) {
        puts("Inventory is empty!");
        return;
    }

    list_each(&inventory->contents, &item_print);
}

void inventory_free(struct inventory *inventory)
{
    list_each(&inventory->contents, &item_free);
    list_free(&inventory->contents);
}

static bool name_finder(void *data, void *arg)
{
    struct item *item = data;

    if (strncmp(item->name, (char *)arg, strlen(item->name)) == 0) {
        return true;
    }
    return false;
}

static bool name_comparer(void *first, void *second)
{
    struct item *first_item = first;
    struct item *second_item = second;

    if (strncmp(first_item->name, second_item->name, strlen(first_item->name)) > 0) {
        return true;
    }
    return false;
}

static void item_print(void *data)
{
    struct item *item = data;
    printf("%s [%s]\n", item->description, item->name);
}

static void item_free(void *data)
{
    free(data);
}
