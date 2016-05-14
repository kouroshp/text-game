#ifndef PERSON_H
#define PERSON_H

#include <stdbool.h>
#include "position.h"
#include "inventory.h"

struct person {
    char *name;
    struct inventory inventory;
    struct position position;
    int health;
    struct item *weapon;
    bool in_combat;
};

void person_init(struct person *person, char *name);
void person_free(struct person *person);

#endif
