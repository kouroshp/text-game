#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "item.h"
#include "inventory.h"
#include "vector.h"
#include "command.h"

void inventory_init(struct inventory* inventory) {
	inventory->size = 0;
	inventory->capacity = 10;

	inventory->contents = malloc(sizeof(struct list));
	list_init(inventory->contents);
}

bool inventory_add(struct inventory* inventory, struct item* item) {
	if (inventory->size + item->weight <= inventory->capacity) {
		list_add(inventory->contents, item);
		inventory->size += item->weight;
		return true;
	}
	return false;
}

void inventory_remove(struct inventory* inventory, int index) {
	// Probably not very efficient
	struct item* item = inventory_get(inventory, index);
	inventory->size -= item->weight;
	list_remove(inventory->contents, index);
}

struct item* inventory_get(struct inventory* inventory, int index) {
	return (struct item*)list_get(inventory->contents, index)->data;
}
