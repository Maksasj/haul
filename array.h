#ifndef HAUL_ARRAY_H
#define HAUL_ARRAY_H

#include <stdlib.h>
#include <assert.h>

typedef struct array_t {
    void** items;

    int capacity;
} array_t;

void create_array(array_t* array, int initial_capacity);

void array_set(array_t* array, int index, void* item);

void* array_get(array_t* array, int index);

int array_empty(array_t* array);

int array_capacity(array_t* array);

void free_array(array_t* array);

void free_array_content(array_t* array);

#ifdef HAUL_IMPLEMENTATION

// Todo

#endif

#endif