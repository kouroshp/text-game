#ifndef COMMAND_H
#define COMMAND_H

#include "vector.h"
#include "context.h"

struct command {
    char *command;
    int (*handler)(struct vector *args, struct context *context);
};

void command_add(struct vector *commands, char *command, int (*handler)(struct vector *args, struct context *context));

#endif
