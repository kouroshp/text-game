#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdbool.h>
#include "item.h"
#include "list.h"
#include "vector.h"

typedef struct
{
	int size;
	int capacity;
	list_t* contents;
} inventory_t;

void inventory_init(inventory_t* inventory);
bool inventory_add(inventory_t* inventory, item_t* item);
void inventory_remove(inventory_t* inventory, int index);
item_t* inventory_get(inventory_t* inventory, int index);

#endif