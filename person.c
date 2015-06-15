#include <stdlib.h>
#include "person.h"
#include "inventory.h"

void person_init(person_t* person, char* name) {
	person->name = name;
	person->inventory = malloc(sizeof(inventory_t));
	inventory_init(person->inventory);
	person->position.x = 0;
	person->position.y = 0;
}