#include "chunk.h"
#include "malloc.h"
#include "arena.h"

void show_chunk(t_chunk *chunk);

#include <stdio.h>
void free(void *ptr)
{
	t_heap **head;
	t_heap *heap;
	t_chunk *chunk;

	if (ptr == NULL)
		return;
	pthread_mutex_lock(&mutex);

	chunk = get_chunk_from_payload(ptr);
	if (search_heap_in_heaps(chunk, &head, &heap))
	{
		if (!chunk_is_corrupt(heap, chunk))
		{
			set_chunk_free(chunk);
			chunk = coalesce_chunk(heap, chunk);
			release_heap_maybe(head, heap);
		}
	}
	pthread_mutex_unlock(&mutex);
}
