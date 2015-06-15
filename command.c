#include "command.h"
#include "vector.h"
#include "context.h"

void command_add(vector_t* commands, char* command, void (*handler)(context_t* context)) {
	command_t* cmd = malloc(sizeof(command_t));
	cmd->command = command;
	cmd->handler = handler;
	vector_add(commands, cmd);
}