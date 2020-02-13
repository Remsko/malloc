#include "align.h"
#include "heap.h"
#include "config.h"
#include "arena.h"
#include "chunk.h"
#include "malloc.h"
#include "debug.h"
#include "ft_printf.h"

pthread_mutex_t g_thread_mutex = PTHREAD_MUTEX_INITIALIZER;

t_chunk *get_free_chunk(t_heap_tree *tree, size_t chunk_size)
{
	t_heap_node *new_heap;
	size_t new_heap_size;
	t_chunk *chunk;

	if ((chunk = search_free_chunk_disorder(tree, tree->root, chunk_size)))
		return chunk;
	new_heap_size = get_heap_size(chunk_size);
	if (new_heap_size < chunk_size)
		return NULL;
	new_heap = arena_unshift(tree, new_heap_size);
	if (new_heap == NULL)
		return NULL;
	chunk = init_chunk(new_heap);
	//show_chunk(chunk);
	split_chunk(new_heap, chunk, chunk_size);
	return chunk;
}

void *malloc_unlocked(size_t size)
{
	t_heap_tree *tree;
	t_chunk *chunk;
	size_t chunk_size;

	if (size == 0)
		size = 1;
	chunk_size = memory_align(size + sizeof(t_chunk));
	if (chunk_size < size)
		return NULL;
	tree = get_arena_heap_tree_by_size(chunk_size);
	chunk = get_free_chunk(tree, chunk_size);
	if (chunk == NULL)
		return NULL;
	set_chunk_used(chunk);
	return get_chunk_payload(chunk);
}

void *malloc(size_t size)
{
	void *payload;

	//ft_printf("M IN\n");
	pthread_mutex_lock(&g_thread_mutex);
	payload = malloc_unlocked(size);
	pthread_mutex_unlock(&g_thread_mutex);
	//ft_printf("M OUT\n");
	return payload;
}