#include <string.h>
#include "utilities.h"

struct vector* explode(char* str, char* c) 
{
	struct vector* tokens = malloc(sizeof(struct vector));
	vector_init(tokens, sizeof(char*));

	char* token = strtok(str, c);

	while (token != NULL) {
		remove_newline(token);
		vector_add(tokens, token);
		token = strtok(NULL, c);
	}

	return tokens;
}

void remove_newline(char* str) 
{
	str[strcspn(str, "\n")] = 0;
}
