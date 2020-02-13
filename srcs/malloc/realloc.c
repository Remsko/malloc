#include "chunk.h"
#include "align.h"
#include "malloc.h"
#include "libc.h"
#include "debug.h"
#include "ft_printf.h"

void *realloc_unlocked(void *ptr, size_t size)
{
	void *new;
	t_heap_tree *tree;
	t_heap_node *heap;
	t_chunk *chunk;

	if (ptr == NULL)
		return malloc_unlocked(size);
	chunk = get_chunk_from_payload(ptr);
	if (!search_chunk(chunk, &tree, &heap))
		return NULL;
	if (chunk_is_corrupt(heap, chunk))
		return NULL;
	if (size <= get_payload_size(chunk))
		return ptr;
	new = malloc_unlocked(size);
	if (new != NULL)
		ft_memmove(new, get_chunk_payload(chunk), get_payload_size(chunk));
	free_unlocked(ptr);
	return new;
}

void *realloc(void *ptr, size_t size)
{
	void *re;

	ft_printf("R IN\n");
	pthread_mutex_lock(&g_thread_mutex);
	re = realloc_unlocked(ptr, size);
	pthread_mutex_unlock(&g_thread_mutex);
	ft_printf("R OUT\n");

	return re;
}