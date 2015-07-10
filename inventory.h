#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdbool.h>
#include "item.h"
#include "list.h"
#include "vector.h"

struct inventory {
	int size;
	int capacity;
	struct list* contents;
};

void inventory_init(struct inventory* inventory);
bool inventory_add(struct inventory* inventory, struct item* item);
void inventory_remove(struct inventory* inventory, int index);
struct item* inventory_get(struct inventory* inventory, int index);

#endif
