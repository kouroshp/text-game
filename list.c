#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_init(struct list* list) {
	list->begin = NULL;
	list->end = NULL;
	list->size = 0;
}

void list_add(struct list* list, void* element) {
	struct node* node = malloc(sizeof(struct node));
	node->data = element;
	node->next = NULL;

	// If list is empty, set the begin to new node
	if (list->begin == NULL) {
		list->begin = node;
		list->size += 1;
	}
	else {
		struct node* last = list->end;
		last->next = node;
		list->size += 1;
	}

	// Update last item to point to latest addition
	list->end = node;
}

struct node* list_get(struct list* list, int index) {
	// If requesting last node, just return it
	if (index == list->size) {
		return list->end;
	}

	struct node* node = list->begin;

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

void list_remove(struct list* list, int index) {
	// Get node prior to one to remove
	struct node* prev = list_get(list, index - 1);
	struct node* curr = prev->next;

	// Update links
	if (index < list->size) {
		struct node* next = curr->next;
		prev->next = next;
	}
	else {
		prev->next = NULL;
	}

	// Remove node
	free(curr);
	list->size -= 1;
}

void list_each(struct list* list, void (*function)(void* data)) {
	struct node* node = list->begin;

	for (int i = 0; i < list->size; i++) {
		function(node->data);
		node = node->next;
	}
}
