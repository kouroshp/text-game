#include "location.h"
#include "inventory.h"

void location_init(struct location* location, char* name, char* description)
{
    location->name = name;
    location->description = description;
    location->inventory = malloc(sizeof(struct inventory));
    inventory_init(location->inventory);
    location->people = malloc(sizeof(struct vector));
    vector_init(location->people, sizeof(struct person*));
}

void location_free(struct location* location)
{
    inventory_free(location->inventory);
    free(location->inventory);

    for (int i = 0; i < location->people->size; i++) {
        person_free(location->people->data[i]);
    }

    vector_free(location->people);
    free(location->people);
}
