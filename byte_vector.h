#ifndef HAUL_BYTE_VECTOR_H
#define HAUL_BYTE_VECTOR_H

#include <stdlib.h>
#include <assert.h>

typedef unsigned char haul_byte_t;
typedef unsigned long long haul_size_t;

typedef struct {
    haul_byte_t *data;
    haul_size_t size;
    haul_size_t capacity;
} byte_vector_t;

void create_byte_vector(byte_vector_t *arr, haul_size_t initialCapacity);

void byte_vector_resize(byte_vector_t *arr, haul_size_t newCapacity);

void byte_vector_push(byte_vector_t *arr, haul_byte_t value);

void free_byte_vector(byte_vector_t *arr);

#ifdef HAUL_IMPLEMENTATION

void create_byte_vector(byte_vector_t *arr, haul_size_t initialCapacity) {
    arr->data = (haul_byte_t *) malloc(initialCapacity * sizeof(haul_byte_t));
    arr->size = 0;
    arr->capacity = initialCapacity;
}

void byte_vector_resize(byte_vector_t *arr, haul_size_t newCapacity) {
    arr->data = (haul_byte_t *) realloc(arr->data, newCapacity * sizeof(haul_byte_t));
    arr->capacity = newCapacity;
}

void byte_vector_push(byte_vector_t *arr, haul_byte_t value) {
    if (arr->size == arr->capacity)
        byte_vector_resize(arr, arr->capacity * 2); // Double the capacity
    
    arr->data[arr->size++] = value;
}

void free_byte_vector(byte_vector_t *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = arr->capacity = 0;
}

#endif

#endif