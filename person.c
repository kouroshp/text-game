#include <stdlib.h>
#include "person.h"
#include "inventory.h"

void person_init(struct person* person, char* name)
{
	person->name = name;
	person->inventory = malloc(sizeof(struct inventory));
	inventory_init(person->inventory);
	person->position.x = 0;
	person->position.y = 0;
}

void person_free(struct person* person)
{
    inventory_free(person->inventory);
    free(person->inventory);
}
