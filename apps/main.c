#include "j85_assert.h"
#include "j85_memory.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Hello, world!\n");

    j85_assert(j85_memory_api_create());
    void* mem = j85_memory_api->system->alloc(42);
    void* mem2 = j85_memory_api->system->calloc(48, 42);
    mem = j85_memory_api->system->realloc(mem, 48);
    j85_memory_api->system->free(mem);
    j85_memory_api->system->free(mem2);
    j85_memory_api_destroy();

    return EXIT_SUCCESS;
}
