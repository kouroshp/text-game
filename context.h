#ifndef CONTEXT_H
#define CONTEXT_H

#include "person.h"

typedef struct {
	person_t* player;
	void* map[10][10];
} context_t;

#endif