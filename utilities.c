#include <string.h>
#include "utilities.h"

struct vector *strsplit(char *str, char *sep)
{
    struct vector *tokens = malloc(sizeof(*tokens));
    vector_init(tokens, sizeof(char *));

    char *token = strtok(str, sep);

    while (token != NULL) {
        remove_newline(token);
        vector_add(tokens, token);
        token = strtok(NULL, sep);
    }

    return tokens;
}

void remove_newline(char *str)
{
    str[strcspn(str, "\n")] = 0;
}
