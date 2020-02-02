#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void *get_some_memory(size_t size);
void *release_some_memory(void *memory, size_t size);

#endif