#ifndef LOCATION_H
#define LOCATION_H

#include "inventory.h"
#include "vector.h"

struct location {
    char *name;
    char *description;
    struct inventory inventory;
    struct vector people;
};

void location_init(struct location *location, char *name, char *description);
void location_free(struct location *location);

#endif
