#ifndef COMMAND_H
#define COMMAND_H

#include "vector.h"
#include "context.h"

struct command {
    const char *command;
    int (*handler)(struct vector *args, struct context *context);
};

void command_add(struct vector *commands, const char *command, int (*handler)(struct vector *args, struct context *context));

#endif
