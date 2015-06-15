#ifndef LIST_H
#define LIST_H

typedef struct node {
	void* data;
	struct node* next;
} node_t;

typedef struct {
	node_t* begin;
	node_t* end;
	int size;
} list_t;

void list_init(list_t* list);
void list_add(list_t* list, void* element);
node_t* list_get(list_t* list, int index);
void list_remove(list_t* list, int index);

#endif