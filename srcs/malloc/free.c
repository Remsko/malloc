#include "chunk.h"
#include "malloc.h"
#include "arena.h"

void free_unlocked(void *ptr)
{
	t_heap **head;
	t_heap *heap;
	t_chunk *chunk;

	if (ptr == NULL)
		return;
	chunk = get_chunk_from_payload(ptr);
	if (search_heap_in_heaps(chunk, &head, &heap))
	{
		if (chunk_is_corrupt(heap, chunk))
			return;
		set_chunk_free(chunk);
		chunk = coalesce_chunk(heap, chunk);
		release_heap_maybe(head, heap);
	}
}

void free(void *ptr)
{
	pthread_mutex_lock(&mutex);
	free_unlocked(ptr);
	pthread_mutex_unlock(&mutex);
}
