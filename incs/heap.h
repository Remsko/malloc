#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef struct s_heap
{
	struct s_heap *next;
	size_t size;
} t_heap;

t_heap *get_heap(void *alloc);
t_heap *new_heap(void *alloc, size_t alloc_size);
t_heap *push_heap(t_heap **head, t_heap *new);
t_heap *push_new_heap(t_heap **head, void *alloc, size_t alloc_size);

#endif