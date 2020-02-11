#ifndef HEAP_H
#define HEAP_H

#include "config.h"
#include "rb_tree_42.h"
#include <pthread.h>

typedef struct s_heap
{
	struct s_heap *left;
	struct s_heap *right;
	struct s_heap *parent;
	size_t size;
	t_rb_color color;
	char padding[8];
} t_heap;

t_heap *get_heap(void *alloc);
size_t get_heap_size(size_t chunk_size);
t_heap *new_heap(void *alloc, size_t alloc_size);
t_heap *unshift_heap(t_heap **head, t_heap *new);
t_heap *unshift_new_heap(t_heap **head, void *alloc, size_t alloc_size);

void delete_heap(t_heap **head, t_heap *delete);
void release_heap_maybe(t_heap **head, t_heap *heap);

#endif
