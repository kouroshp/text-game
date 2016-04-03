#include "location.h"
#include "inventory.h"
#include "person.h"

void location_init(struct location *location, char *name, char *description)
{
    location->name = name;
    location->description = description;
    inventory_init(&location->inventory);
    vector_init(&location->people, sizeof(struct person *));
}

void location_free(struct location *location)
{
    for (int i = 0; i < location->people.size; i++) {
        person_free(vector_get(&location->people, i));
        free(vector_get(&location->people, i));
    }

    vector_free(&location->people);
    inventory_free(&location->inventory);
}
