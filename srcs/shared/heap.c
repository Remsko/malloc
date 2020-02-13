#include "heap.h"
#include "config.h"
#include "chunk.h"
#include "arena.h"
#include "memory.h"
#include "align.h"
#include "libc.h"
#include "debug.h"
#include "ft_printf.h"

void del(t_rb_node *node)
{
	t_heap_node *heap;

	heap = (t_heap_node *)node;
	release_some_memory((void *)heap, heap->size);
}

void release_heap_maybe(t_heap_tree *tree, t_heap_node *heap)
{
	t_chunk *chunk;

	chunk = get_first_chunk(heap);
	if (heap->size - sizeof(t_heap_node) == get_chunk_size(chunk))
	{
		deleteNode((t_rb_tree *)tree, (t_rb_node *)heap, del);
	}
}

size_t get_heap_size(size_t chunk_size)
{
	t_config config;
	t_config_type type;

	type = get_config_type(chunk_size);
	if (type == LARGE)
		return page_align(chunk_size + sizeof(t_heap_node));
	config = get_config(type);
	return config.heap_size;
}

t_heap_node *get_heap(void *memory)
{
	return (t_heap_node *)memory;
}

t_heap_node *new_heap(void *memory, size_t size)
{
	t_heap_node *heap;

	heap = get_heap(memory);
	heap->size = size;
	return heap;
}

// int cmp_heap_f(void *heap1, void *heap2)
// {
// 	int ret;

// 	if (heap1 < heap2)
// 		ret = -1;
// 	else if (heap1 > heap2)
// 		ret = 1;
// 	else
// 		ret = 0;
// 	return ret;
// }

static int cmp_ptr(t_rb_node *n1, t_rb_node *n2)
{
	return (void *)n1 < (void *)n2;
}
#include "ft_printf.h"
t_heap_node *unshift_heap(t_heap_tree *tree, t_heap_node *new)
{
	//ft_printf("shift1");
	insertNode((t_rb_tree *)tree, (t_rb_node *)new, &cmp_ptr);
	//ft_printf("shift2");
	return new;
}

t_heap_node *unshift_new_heap(t_heap_tree *tree, void *memory, size_t size)
{
	t_heap_node *new;

	new = new_heap(memory, size);
	unshift_heap(tree, new);
	return new;
}
