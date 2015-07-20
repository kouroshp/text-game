#ifndef CONTEXT_H
#define CONTEXT_H

#include "vector.h"
#include "person.h"

struct context {
	struct person* player;
	void* map[10][10];
	struct vector* args;
};

#endif
