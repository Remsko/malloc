#include "heap.h"
#include "config.h"
#include "chunk.h"
#include "arena.h"
#include "memory.h"
#include "align.h"
#include "libc.h"
#include "rb_tree_42.h"
#include "debug.h"

void del(t_rb_tree *rb)
{
	release_some_memory((void *)rb, ((t_heap *)rb)->size);
}

void release_heap_maybe(t_heap **head, t_heap *heap)
{
	t_chunk *chunk;

	(void)head;
	chunk = get_first_chunk(heap);
	if (heap->size - sizeof(t_heap) == get_chunk_size(chunk))
	{
		rb_tree_delete_node((t_rb_tree **)head, (t_rb_tree *)heap, &del);
		release_some_memory((void *)heap, heap->size);
	}
}

size_t get_heap_size(size_t chunk_size)
{
	t_config config;
	t_config_type type;

	type = get_config_type(chunk_size);
	if (type == LARGE)
		return page_align(chunk_size + sizeof(t_heap));
	config = get_config(type);
	return config.heap_size;
}

t_heap *get_heap(void *memory)
{
	return (t_heap *)memory;
}

t_heap *new_heap(void *memory, size_t size)
{
	t_heap *heap;

	heap = get_heap(memory);
	heap->size = size;
	return heap;
}

int cmp_heap_f(void *heap1, void *heap2)
{
	int ret;

	if (heap1 < heap2)
		ret = -1;
	else if (heap1 > heap2)
		ret = 1;
	else
		ret = 0;
	return ret;
}

t_heap *unshift_heap(t_heap **head, t_heap *new)
{
	rb_tree_heap_insert((t_rb_tree **)head, (t_rb_tree *)new, &cmp_heap_f);
	return new;
}

t_heap *unshift_new_heap(t_heap **head, void *memory, size_t size)
{
	t_heap *new;

	new = rb_tree_heap_new(memory, size);
	unshift_heap(head, new);
	return new;
}
