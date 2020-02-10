#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#include <stdbool.h>
#include <pthread.h>

#define DEBUG 1

void *malloc(size_t size);
void *calloc(size_t count, size_t size);
void *valloc(size_t size);
void *realloc(void *ptr, size_t size);
void *reallocf(void *ptr, size_t size);
void free(void *ptr);
void show_alloc_mem(void);

void *malloc_unlocked(size_t size);
void *realloc_unlocked(void *ptr, size_t size);
void free_unlocked(void *ptr);

extern pthread_mutex_t mutex;

#endif