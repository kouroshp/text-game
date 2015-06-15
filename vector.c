#include <stdlib.h>
#include "vector.h"

void vector_init(vector_t* vector, size_t element_size) {
	vector->capacity = VECTOR_CAPACITY;
	vector->size = 0;
	vector->element_size = element_size;
	vector->data = malloc(vector->capacity*vector->element_size);
}

void vector_add(vector_t* vector, void* element) {
	// If it's full, resize
	if (vector->size == vector->capacity) {
		vector_resize(vector);
	}

	vector->data[vector->size] = element;
	vector->size++;
}

void* vector_get(vector_t* vector, int index) {
	if (index < 0) {
		return vector->data[0];
	}
	if (index > vector->size) {
		return vector->data[vector->size];
	}
	return vector->data[index];
}

void vector_resize(vector_t* vector) {
	// Double size of array
	vector->capacity *= 2;
	vector->data = realloc(vector->data, vector->capacity * vector->element_size);
}