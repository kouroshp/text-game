#include <stdlib.h>
#include <stdbool.h>
#include "person.h"
#include "inventory.h"

void person_init(struct person *person, const char *name)
{
    person->name = name;
    inventory_init(&person->inventory);
    person->position.x = 0;
    person->position.y = 0;
    person->health = 100;
    person->weapon = NULL;
    person->in_combat = false;
}

void person_free(struct person *person)
{
    inventory_free(&person->inventory);
}
