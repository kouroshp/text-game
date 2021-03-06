#ifndef LOCATION_H
#define LOCATION_H

#include <stdbool.h>
#include "inventory.h"
#include "vector.h"

struct area {
    const char *name;
    const char *description;
};

struct location {
    struct area *area;
    bool exit;
    struct inventory inventory;
    struct vector people;
};

void area_init(struct area *area, const char *name, const char *description);
void location_init(struct location *location);
void location_free(struct location *location);

#endif
