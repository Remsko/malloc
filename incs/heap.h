#ifndef HEAP_H
#define HEAP_H

#include "config.h"

typedef struct s_heap
{
	struct s_heap *next;
	size_t size;
} t_heap;

t_heap *get_heap(void *alloc);
t_heap *new_heap(void *alloc, size_t alloc_size);
t_heap *unshift_heap(t_heap **head, t_heap *new);
t_heap *unshift_new_heap(t_heap **head, void *alloc, size_t alloc_size);
size_t get_heap_size(t_config_type type);
void delete_heap(t_heap **head, t_heap *delete);

#endif
