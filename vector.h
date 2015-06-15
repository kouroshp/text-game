#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define VECTOR_CAPACITY 50;

typedef struct {
	void** data;
	int capacity;
	int size;
	size_t element_size;
} vector_t;

void vector_init(vector_t* vector, size_t element_size);
void vector_add(vector_t* vector, void* element);
void* vector_get(vector_t* vector, int index);
void vector_resize(vector_t* vector);

#endif