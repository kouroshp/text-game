#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "item.h"
#include "inventory.h"

static bool name_comparer(void *data, char *arg);
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

struct item *inventory_remove(struct inventory *inventory, char *name)
{
    void *data = list_find_and_remove(&inventory->contents, &name_comparer, name);
    if (data == NULL) {
        return NULL;
    }

    struct item *item = (struct item *)data;
    inventory->size -= item->weight;
    return item;
}

struct item *inventory_get(struct inventory *inventory, char *name)
{
    void *data = list_find(&inventory->contents, &name_comparer, name);
    if (data == NULL) {
        return NULL;
    }
    return (struct item *)data;
}

void inventory_contents_print(struct inventory *inventory)
{
    if (inventory->size == 0) {
        printf("Inventory is empty!\n");
        return;
    }

    list_each(&inventory->contents, &item_print);
}

void inventory_free(struct inventory *inventory)
{
    list_each(&inventory->contents, &item_free);
    list_free(&inventory->contents);
}

static bool name_comparer(void *data, char *arg)
{
    struct item *item = (struct item *)data;

    if (strncmp(item->name, arg, strlen(item->name)) == 0) {
        return true;
    }
    return false;
}

static void item_print(void *data)
{
    struct item *item = (struct item *)data;
    printf("%s [%s]\n", item->description, item->name);
}

static void item_free(void *data)
{
    free(data);
}
