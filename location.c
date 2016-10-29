#include "location.h"
#include "inventory.h"
#include "person.h"
#include <stdbool.h>

void area_init(struct area *area, const char *name, const char *description)
{
    area->name = name;
    area->description = description;
}

void location_init(struct location *location)
{
    location->area = NULL;
    location->exit = false;
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
