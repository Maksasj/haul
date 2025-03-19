#ifndef HAUL_BYTE_VECTOR_H
#define HAUL_BYTE_VECTOR_H

#include <stdlib.h>
#include <assert.h>

#include "haul_types.h"

typedef struct {
    haul_u8_t *data;
    haul_size_t size;
    haul_size_t capacity;
} byte_vector_t;

void create_byte_vector(byte_vector_t *arr, haul_size_t initial_capacity);

void byte_vector_resize(byte_vector_t *arr, haul_size_t new_capacity);

void byte_vector_push_byte(byte_vector_t *arr, haul_u8_t value);

void byte_vector_push8(byte_vector_t *arr, haul_u8_t value);
void byte_vector_push16(byte_vector_t *arr, haul_u16_t value);
void byte_vector_push32(byte_vector_t *arr, haul_u32_t value);
void byte_vector_push64(byte_vector_t *arr, haul_u64_t value);

void free_byte_vector(byte_vector_t *arr);

#ifdef HAUL_IMPLEMENTATION

void create_byte_vector(byte_vector_t *arr, haul_size_t initial_capacity) {
    arr->data = (haul_u8_t *) malloc(initial_capacity * sizeof(haul_u8_t));
    arr->size = 0;
    arr->capacity = initial_capacity;
}

void byte_vector_resize(byte_vector_t *arr, haul_size_t new_capacity) {
    arr->data = (haul_u8_t *) realloc(arr->data, new_capacity * sizeof(haul_u8_t));
    arr->capacity = new_capacity;
}

void byte_vector_push_byte(byte_vector_t *arr, haul_byte_t value) {
    if (arr->size == arr->capacity)
        byte_vector_resize(arr, arr->capacity * 2); // Double the capacity
    
    arr->data[arr->size++] = value;
}

void byte_vector_push8(byte_vector_t *arr, haul_u8_t value) {
    byte_vector_push_byte(arr, value);   
}

void byte_vector_push16(byte_vector_t *arr, haul_u16_t value) {
    haul_u8_t* split = (haul_u8_t*) &value;
    byte_vector_push8(arr, split[0]);   
    byte_vector_push8(arr, split[1]);
}

void byte_vector_push32(byte_vector_t *arr, haul_u32_t value) {
    haul_u16_t* split = (haul_u16_t*) &value;
    byte_vector_push16(arr, split[0]);   
    byte_vector_push16(arr, split[1]);
}

void byte_vector_push64(byte_vector_t *arr, haul_u64_t value) {
    haul_u32_t* split = (haul_u32_t*) &value;
    byte_vector_push32(arr, split[0]);   
    byte_vector_push32(arr, split[1]);
}

void free_byte_vector(byte_vector_t *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = arr->capacity = 0;
}

#endif

#endif