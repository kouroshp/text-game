#include "command.h"
#include "vector.h"
#include "context.h"

void command_add(struct vector *commands, char *command, void (*handler)(struct vector *args, struct context *context))
{
    struct command *cmd = malloc(sizeof(*cmd));
    cmd->command = command;
    cmd->handler = handler;
    vector_add(commands, cmd);
}
