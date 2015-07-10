#include "utilities.h"
#include "string.h"

struct vector* explode(char* str, char* c) {
	struct vector* tokens = malloc(sizeof(struct vector*));
	vector_init(tokens, sizeof(char*));

	char* token = strtok(str, c);

	while (token != NULL) {
		vector_add(tokens, token);
		token = strtok(NULL, c);
	}

	return tokens;
}