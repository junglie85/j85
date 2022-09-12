#include "j85/assert.h"
#include "j85/memory.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Hello, world!\n");

    j_assert(j_memory_api_create());
    void* mem = j_memory_api->system->alloc(42);
    void* mem2 = j_memory_api->system->calloc(48, 42);
    mem = j_memory_api->system->realloc(mem, 48);
    j_memory_api->system->free(mem);
    j_memory_api->system->free(mem2);
    j_memory_api_destroy();

    return EXIT_SUCCESS;
}
