#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>

#define VECTOR_CAPACITY 50;

struct vector {
    void **data;
    unsigned int capacity;
    unsigned int size;
    size_t element_size;
};

void vector_init(struct vector *vector, size_t element_size);
void vector_add(struct vector *vector, void *element);
bool vector_remove(struct vector *vector, unsigned int index);
void *vector_get(struct vector *vector, unsigned int index);
void vector_free(struct vector *vector);

#endif
