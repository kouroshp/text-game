#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define VECTOR_CAPACITY 50;

struct vector {
	void** data;
	int capacity;
	int size;
	size_t element_size;
};

void vector_init(struct vector* vector, size_t element_size);
void vector_add(struct vector* vector, void* element);
void* vector_get(struct vector* vector, int index);
void vector_resize(struct vector* vector);
void vector_free(struct vector* vector);

#endif
