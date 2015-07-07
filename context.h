#ifndef CONTEXT_H
#define CONTEXT_H

#include "vector.h"
#include "person.h"

typedef struct {
	person_t* player;
	void* map[10][10];
	vector_t* args;
} context_t;

#endif