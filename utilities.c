#include "utilities.h"
#include "string.h"

vector_t* explode(char* str, char* c) {
	vector_t* tokens = malloc(sizeof(vector_t*));
	vector_init(tokens, sizeof(char*));

	char* token = strtok(str, c);

	while (token != NULL) {
		vector_add(tokens, token);
		token = strtok(NULL, c);
	}

	return tokens;
}