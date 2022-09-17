#ifndef J85_MEMORY_H
#define J85_MEMORY_H

#include "j85_api_types.h"

typedef struct j85_allocator_i {
    void* (*alloc)(size_t size);
    void* (*calloc)(size_t count, size_t size);
    void* (*realloc)(void* data, size_t size);
    void (*free)(void* data);
} j85_allocator_i;

typedef struct j85_memory_api_t {
    j85_allocator_i* system;
} j85_memory_api_t;

j85_memory_api_t* j85_memory_api;

bool j85_memory_api_create(void);
void j85_memory_api_destroy(void);

#endif // J85_MEMORY_H
