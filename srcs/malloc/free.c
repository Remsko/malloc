#include "chunk.h"
#include "malloc.h"
#include "arena.h"

void show_chunk(t_chunk *chunk);

#include <stdio.h>
void free(void *ptr)
{
	t_heap *heap;
	t_chunk *chunk;
	t_config_type type;

	if (ptr == NULL)
		return;
	pthread_mutex_lock(&g_thread_mutex);

	chunk = get_chunk_from_payload(ptr);
	if (!chunk_is_referenced(&heap, &type, chunk) || chunk_is_corrupt(heap, chunk))
		return;
	set_chunk_free(chunk);
	chunk = coalesce_chunk(heap, chunk);
	//printf("%s : 0x%lX %zu octets\n", config_type_to_string(type), (unsigned long)heap, heap->size);
	//show_chunk(chunk);
	release_heap_maybe(heap, type);
	//printf("/");
	pthread_mutex_unlock(&g_thread_mutex);
}
