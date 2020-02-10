#include "chunk.h"
#include "align.h"
#include "malloc.h"
#include "libc.h"

void *realloc(void *ptr, size_t size)
{
	void *new;
	t_heap **head;
	t_heap *heap;
	t_chunk *chunk;

	if (ptr == NULL)
		return malloc(size);
	pthread_mutex_lock(&mutex);
	chunk = get_chunk_from_payload(ptr);
	if (!search_heap_in_heaps(chunk, &head, &heap))
	{
		pthread_mutex_unlock(&mutex);
		return NULL;
	}
	if (chunk_is_corrupt(heap, chunk))
	{
		pthread_mutex_unlock(&mutex);
		return NULL;
	}
	if (size <= get_payload_size(chunk))
	{
		pthread_mutex_unlock(&mutex);
		return ptr;
	}
	pthread_mutex_unlock(&mutex);
	new = malloc(size);
	if (new != NULL)
		ft_memmove(new, get_chunk_payload(chunk), get_payload_size(chunk));
	free(ptr);
	return new;
}