#include "chunk.h"
#include "malloc.h"
#include "arena.h"
#include "debug.h"
#include "ft_printf.h"

void free_unlocked(void *ptr)
{
	t_heap_tree *tree;
	t_heap_node *heap;
	t_chunk *chunk;

	if (ptr == NULL)
		return;
	chunk = get_chunk_from_payload(ptr);
	if (!search_chunk(chunk, &tree, &heap))
		return;
	if (chunk_is_corrupt(heap, chunk))
		return;
	set_chunk_free(chunk);
	chunk = coalesce_chunk(heap, chunk);
	release_heap_maybe(tree, heap);
}

void free(void *ptr)
{
	pthread_mutex_lock(&g_thread_mutex);
	free_unlocked(ptr);
	pthread_mutex_unlock(&g_thread_mutex);
}
