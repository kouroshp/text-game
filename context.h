#ifndef CONTEXT_H
#define CONTEXT_H

#include "vector.h"
#include "person.h"
#include "location.h"

struct context {
    struct person* player;
    struct location* map[10][10];
    struct vector* args;
};

#endif
