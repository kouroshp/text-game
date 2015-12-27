#ifndef ITEM_H
#define ITEM_H

struct item {
	char* name;
	int weight;
};

void item_free(struct item* item);

#endif
