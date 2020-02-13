#ifndef HEAP_H
#define HEAP_H

#include "rb_tree.h"
#include "config.h"
#include <pthread.h>

typedef struct s_heap_node
{
	struct s_heap_node *left;
	struct s_heap_node *right;
	struct s_heap_node *parent;
	size_t size;
	t_node_color color;
	char padding[8];
} t_heap_node;

typedef struct s_heap_tree
{
	t_heap_node *root;
	t_heap_node *nil;
} t_heap_tree;

// t_heap *get_heap(void *alloc);
// size_t get_heap_size(size_t chunk_size);
// t_heap *new_heap(void *alloc, size_t alloc_size);
// t_heap *unshift_heap(t_heap **head, t_heap *new);
// t_heap *unshift_new_heap(t_heap **head, void *alloc, size_t alloc_size);

// void delete_heap(t_heap **head, t_heap *delete);
// void release_heap_maybe(t_heap **head, t_heap *heap);t_heap_node *get_heap(void *memory)

void release_heap_maybe(t_heap_tree *tree, t_heap_node *heap);
size_t get_heap_size(size_t chunk_size);
t_heap_node *get_heap(void *memory);
t_heap_node *new_heap(void *memory, size_t size);
t_heap_node *unshift_heap(t_heap_tree *tree, t_heap_node *new);
t_heap_node *unshift_new_heap(t_heap_tree *tree, void *memory, size_t size);

#endif
