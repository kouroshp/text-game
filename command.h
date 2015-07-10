#ifndef COMMAND_H
#define COMMAND_H

#include "vector.h"
#include "context.h"

struct command {
	char* command;
	void (*handler)(struct context* context);
};

void command_add(struct vector* commands, char* command, void (*handler)(struct context* context));

#endif