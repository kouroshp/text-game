#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdbool.h>
#include "item.h"
#include "list.h"

struct inventory {
    int size;
    int capacity;
    struct list contents;
};

void inventory_init(struct inventory *inventory);
bool inventory_add(struct inventory *inventory, struct item *item);
struct item *inventory_remove(struct inventory *inventory, char *name);
struct item *inventory_get(struct inventory *inventory, char *name);
void inventory_free(struct inventory *inventory);
void inventory_contents_print(struct inventory *inventory);

#endif
