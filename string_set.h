#ifndef HAUL_STRING_SET_H
#define HAUL_STRING_SET_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "vector.h"

typedef struct {
    vector_t items;
} string_set_t;

void create_string_set(string_set_t *set, haul_size_t initial_capacity);

int string_set_has(string_set_t *set, const char* value);
void string_set_insert(string_set_t *set, char* value);
void string_set_erase(string_set_t *set, char* value);

void free_string_set(string_set_t *arr);

#ifdef HAUL_IMPLEMENTATION

void create_string_set(string_set_t *set, haul_size_t initial_capacity) {
    create_vector(&set->items, initial_capacity);
}

int string_set_has(string_set_t *set, const char* value) {
    for(int i = 0; i < vector_size(&set->items); ++i) {
        if(strcmp(vector_get(&set->items, i), value) == 0)
            return 1;
    }    

    return 0;
}

void string_set_insert(string_set_t *set, char* value) {
    if(string_set_has(set, value))
        return;

    vector_push(&set->items, value);
}

void string_set_erase(string_set_t *set, char* value) {
    if(!string_set_has(set, value))
        return;

    vector_t new_vector;
    create_vector(&new_vector, set->items.capacity);

    for(int i = 0; i < vector_size(&set->items); ++i) {
        if(strcmp(vector_get(&set->items, i), value) != 0)
            vector_push(&set->items, value);
    }  

    free_vector(&set->items);
    set->items = new_vector;
}

void free_string_set(string_set_t *set) {
    free_vector(&set->items);
}

#endif

#endif