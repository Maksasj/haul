#ifndef HAUL_VECTOR_H
#define HAUL_VECTOR_H

#include <stdlib.h>
#include <assert.h>

typedef struct vector_t {
    void** items;

    int capacity;
    int stored;
} vector_t;

void create_vector(vector_t* vector, int initial_capacity);

void vector_push(vector_t* vector, void* item);

void* vector_get(vector_t* vector, int index);

void* vector_pop(vector_t* vector);

int vector_empty(vector_t* vector);

int vector_size(vector_t* vector);

int vector_capacity(vector_t* vector);

void free_vector(vector_t* vector);

void free_vector_content(vector_t* vector);

#ifdef HAUL_IMPLEMENTATION

void create_vector(vector_t* vector, int initial_capacity) {
    assert(initial_capacity > 0);

    vector->items = calloc(initial_capacity, sizeof(void*));

    vector->stored = 0;
    vector->capacity = initial_capacity;
}

void vector_push(vector_t* vector, void* item) {
    if(vector->stored + 1 > vector->capacity) {
        vector->capacity = vector->capacity * 2;

        // Todo check if items is null
        vector->items = realloc(vector->items, vector->capacity * sizeof(void*));
    }

    vector->items[vector->stored] = item;
    ++vector->stored;
}

void* vector_get(vector_t* vector, int index) {
    if(vector->stored <= index) {
        return NULL;
    }

    return vector->items[index];
}

void* vector_pop(vector_t* vector) {
    if(vector->stored == 0) {
        return NULL;
    }

    --vector->stored;
    void* popped_value = vector->items[vector->stored];

    if(vector->stored > 10 && (vector->stored <= vector->capacity / 2)) {
        vector->capacity = vector->capacity / 2;

        // Todo check if items is null
        vector->items = realloc(vector->items, vector->capacity * sizeof(void*));
    }

    return popped_value;
}

int vector_empty(vector_t* vector) {
    return vector->stored == 0;
}

int vector_size(vector_t* vector) {
    return vector->stored;
}

int vector_capacity(vector_t* vector) {
    return vector->capacity;
}

void free_vector(vector_t* vector) {
    free(vector->items);
}

void free_vector_content(vector_t* vector) {
    for(int i = 0; i < vector->stored; ++i) {
        free(vector->items[i]);
    }
}

#endif

#endif