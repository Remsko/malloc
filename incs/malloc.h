#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#include <stdbool.h>

#define DEBUG 1

void *malloc(size_t size);
void free(void *ptr);

#endif