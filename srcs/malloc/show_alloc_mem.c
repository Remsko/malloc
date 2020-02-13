#include "heap.h"
#include "chunk.h"
#include "config.h"
#include "arena.h"
#include "malloc.h"
#include "ft_printf.h"
#include "debug.h"
#include <stdio.h>

void show_chunk(t_chunk *chunk)
{
	// if (!chunk_is_free(chunk))
	ft_printf("0x%lX - 0x%lX [%u]: next(%zu octets) prev(%zu octets)\n",
			  (unsigned long)chunk,
			  (unsigned long)get_next_chunk(chunk),
			  (unsigned)chunk_is_free(chunk),
			  get_chunk_size(chunk),
			  chunk->backward);
}

void show_heap(t_heap_node *heap, t_config_type type)
{
	t_chunk *chunk;

	ft_printf("%s : 0x%lX - 0x%lX %zu octets\n",
			  config_type_to_string(type),
			  (unsigned long)heap,
			  (unsigned long)((void *)heap + heap->size),
			  heap->size);
	chunk = get_first_chunk(heap);
	while (chunk_is_on_heap(heap, chunk))
	{
		show_chunk(chunk);
		chunk = get_next_chunk(chunk);
	}
}

size_t show_heap_inorder(t_heap_tree *tree, t_heap_node *heap, t_config_type type)
{
	size_t total;

	if (heap == tree->nil)
		return 0;
	total = heap->size;
	total += show_heap_inorder(tree, heap->left, type);
	show_heap(heap, type);
	total += show_heap_inorder(tree, heap->right, type);
	return total;
}

size_t show_heap_and_count(t_config_type type)
{
	t_heap_tree *tree;

	tree = get_arena_heap_tree(type);
	if (tree != NULL)
		return show_heap_inorder(tree, tree->root, type);
	return 0;
}

void show_alloc_mem_unclocked(void)
{
	size_t total;

	total = 0;
	for (t_config_type type = 0; type < TYPES; type++)
		total += show_heap_and_count(type);
	ft_printf("Total : %zu octets\n", total);
}

void show_alloc_mem(void)
{
	pthread_mutex_lock(&g_thread_mutex);
	show_alloc_mem_unclocked();
	pthread_mutex_unlock(&g_thread_mutex);
}