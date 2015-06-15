#ifndef COMMAND_H
#define COMMAND_H

#include "vector.h"
#include "context.h"

typedef struct {
	char* command;
	void (*handler)(context_t* context);
} command_t;

void command_add(vector_t* commands, char* command, void (*handler)(context_t* context));

#endif