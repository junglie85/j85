#ifndef J85_MEMORY_H
#define J85_MEMORY_H

#include "j85/api_types.h"

struct j_memory_api* j_memory_api;

struct j_allocator_i {
    void* (*alloc)(size_t size);
    void* (*calloc)(size_t count, size_t size);
    void* (*realloc)(void* data, size_t size);
    void (*free)(void* data);
};

struct j_memory_api {
    struct j_allocator_i* system;
};

bool j_memory_api_create(void);
void j_memory_api_destroy(void);

#endif // J85_MEMORY_H
