#ifndef PERSON_H
#define PERSON_H

#include "position.h"
#include "inventory.h"

struct person {
    char* name;
    struct inventory inventory;
    struct position position;
    int health;
};

void person_init(struct person* person, char* name);
void person_free(struct person* person);

#endif
