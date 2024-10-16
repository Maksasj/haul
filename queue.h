#ifndef HAUL_QUEUE_H
#define HAUL_QUEUE_H

#include <stdlib.h>
#include <assert.h>

typedef struct queue_t {
    void** items;

    int capacity;
    int stored;
} queue_t;

void create_queue(queue_t* queue, int initial_capacity);

void queue_push(queue_t* queue, void* item);

void* queue_get(queue_t* queue, int index);

void* queue_pop(queue_t* queue);

int queue_empty(queue_t* queue);

int queue_size(queue_t* queue);

int queue_capacity(queue_t* queue);

void free_queue(queue_t* queue);

void free_queue_content(queue_t* queue);

#ifdef HAUL_IMPLEMENTATION

void create_queue(queue_t* queue, int initial_capacity) {
    assert(initial_capacity > 0);

    queue->items = calloc(initial_capacity, sizeof(void*));

    queue->stored = 0;
    queue->capacity = initial_capacity;
}

void queue_push(queue_t* queue, void* item) {
    if(queue->stored + 1 > queue->capacity) {
        queue->capacity = queue->capacity * 2;

        // Todo check if items is null
        queue->items = realloc(queue->items, queue->capacity * sizeof(void*));
    }

    queue->items[queue->stored] = item;
    ++queue->stored;
}

void* queue_get(queue_t* queue, int index) {
    if(queue->stored <= index) {
        return NULL;
    }

    return queue->items[index];
}

void* queue_pop(queue_t* queue) {
    if(queue->stored == 0) {
        return NULL;
    }

    --queue->stored;
    void* popped_value = queue->items[queue->stored];

    if(queue->stored > 10 && (queue->stored <= queue->capacity / 2)) {
        queue->capacity = queue->capacity / 2;

        // Todo check if items is null
        queue->items = realloc(queue->items, queue->capacity * sizeof(void*));
    }

    return popped_value;
}

int queue_empty(queue_t* queue) {
    return queue->stored == 0;
}

int queue_size(queue_t* queue) {
    return queue->stored;
}

int queue_capacity(queue_t* queue) {
    return queue->capacity;
}

void free_queue(queue_t* queue) {
    free(queue->items);
}

void free_queue_content(queue_t* queue) {
    for(int i = 0; i < queue->stored; ++i) {
        free(queue->items[i]);
    }
}

#endif

#endif