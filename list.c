#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_init(list_t* list) {
	list->begin = NULL;
	list->end = NULL;
	list->size = 0;
}

void list_add(list_t* list, void* element) {
	node_t* node = malloc(sizeof(node_t));
	node->data = element;
	node->next = NULL;

	// If list is empty, set the begin to new node
	if (list->begin == NULL) {
		list->begin = node;
	}
	else {
		node_t* last = list->end;
		last->next = node;
		list->size += 1;
	}

	// Update last item to point to latest addition
	list->end = node;
}

node_t* list_get(list_t* list, int index) {
	// If requesting last node, just return it
	if (index == list->size) {
		return list->end;
	}

	node_t* node = list->begin;

	for (int i = 0; i < index - 1; i++) {
		if(i < list->size) {
			node = node->next;
		}
		else {
			return node;
		}
	}

	return node;
}

void list_remove(list_t* list, int index) {
	// Get node prior to one to remove
	node_t* prev = list_get(list, index - 1);
	node_t* curr = prev->next;

	// Update links
	if (index < list->size) {
		node_t* next = curr->next;
		prev->next = next;
	}
	else {
		prev->next = NULL;
	}

	// Remove node
	free(curr);
	list->size -= 1;
}