#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "item.h"
#include "inventory.h"
#include "vector.h"
#include "command.h"

void inventory_init(inventory_t* inventory) {
	inventory->size = 0;
	inventory->capacity = 10;

	inventory->contents = malloc(sizeof(list_t));
	list_init(inventory->contents);
}

bool inventory_add(inventory_t* inventory, item_t* item) {
	if (inventory->size + item->weight <= inventory->capacity) {
		list_add(inventory->contents, item);
		inventory->size += item->weight;
		return true;
	}
	return false;
}

void inventory_remove(inventory_t* inventory, int index) {
	// Probably not very efficient
	item_t* item = inventory_get(inventory, index);
	inventory->size -= item->weight;
	list_remove(inventory->contents, index);
}

item_t* inventory_get(inventory_t* inventory, int index) {
	return (item_t*)list_get(inventory->contents, index)->data;
}