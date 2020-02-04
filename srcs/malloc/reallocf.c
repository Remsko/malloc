#include "malloc.h"

void *reallocf(void *ptr, size_t size)
{
    void *p;

    p = realloc(ptr, size);
    if (!p)
        free(ptr);
    return p;
}