#include "j85/memory.h"

#include <stdio.h>
#include <stdlib.h>

static struct j_memory_api memory_api = {};

static struct j_allocator_i system_allocator = {};

static void* system_alloc(size_t size);
static void* system_calloc(size_t count, size_t size);
static void* system_realloc(void* data, size_t size);
static void system_free(void* data);

bool j_memory_api_create(void)
{
    system_allocator.alloc = &system_alloc;
    system_allocator.calloc = &system_calloc;
    system_allocator.realloc = &system_realloc;
    system_allocator.free = &system_free;
    memory_api.system = &system_allocator;
    j_memory_api = &memory_api;
    printf("j_memory_api_create()\n");

    return true;
}

void j_memory_api_destroy(void)
{
    printf("j_memory_api_destroy()\n");
    system_allocator.alloc = NULL;
    system_allocator.calloc = NULL;
    system_allocator.realloc = NULL;
    system_allocator.free = NULL;
    memory_api.system = NULL;
    j_memory_api = NULL;
}

static void* system_alloc(size_t size)
{
    printf("system_alloc(%zu)\n", size);

    return malloc(size);
}

static void* system_calloc(size_t count, size_t size)
{
    printf("system_calloc(%zu)\n", size);

    return calloc(count, size);
}

static void* system_realloc(void* data, size_t size)
{
    printf("system_realloc(%zu)\n", size);

    return realloc(data, size);
}

static void system_free(void* data)
{
    printf("system_free()\n");

    free(data);
}
