#include "chunk.h"
#include "malloc.h"
#include "arena.h"

t_heap *search_heap(t_chunk *chunk)
{
	t_heap *heap;
	t_config_type type;

	type = get_config_type(chunk->forward);
	heap = *(get_arena_heap_head(type));
	while (heap != NULL)
	{
		if (chunk_is_on_heap(heap, chunk))
			return heap;
		heap = heap->next;
	}
	return NULL;
}

void free(void *ptr)
{
	// t_heap *heap;
	// t_chunk *chunk;

	if (ptr == NULL)
		return;
	// chunk = get_chunk_from_payload(ptr);
	// heap = search_heap(chunk);
	// merge_chunk(chunk);
	// if (heap->size - sizeof(t_heap) == chunk->forward)
	// 	release_memory(heap, heap->size);
}