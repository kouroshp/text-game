#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"

static void vector_resize(struct vector *vector);

void vector_init(struct vector *vector, size_t element_size)
{
    vector->capacity = VECTOR_CAPACITY;
    vector->size = 0;
    vector->element_size = element_size;
    vector->data = malloc(vector->capacity * vector->element_size);
}

void vector_add(struct vector *vector, void *element)
{
    // If it's full, resize
    if (vector->size == vector->capacity) {
        vector_resize(vector);
    }

    vector->data[vector->size] = element;
    vector->size++;
}

bool vector_remove(struct vector *vector, int index)
{
    if (index < 0 || index > vector->size) {
        return false;
    }
    for (int i = index; i < vector->size - 1; i++) {
        vector->data[i] = vector->data[i + 1];
    }
    vector->size--;
    return true;
}

void *vector_get(struct vector *vector, int index)
{
    if (index < 0) {
        return vector->data[0];
    }
    if (index > vector->size) {
        return vector->data[vector->size];
    }
    return vector->data[index];
}

static void vector_resize(struct vector *vector)
{
    // Double size of array
    vector->capacity *= 2;
    vector->data = realloc(vector->data, vector->capacity * vector->element_size);
}

void vector_free(struct vector *vector)
{
    free(vector->data);
}
