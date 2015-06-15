#ifndef PERSON_H
#define PERSON_H

#include "position.h"
#include "inventory.h"

typedef struct {
	char* name;
	inventory_t* inventory;
	position_t position;
} person_t;

void person_init(person_t* person, char* name);

#endif