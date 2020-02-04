#include "chunk.h"
#include "malloc.h"
#include "arena.h"
#include "memory.h"

void free(void *ptr)
{
	t_heap *heap;
	t_chunk *chunk;

	if (ptr == NULL)
		return;
	chunk = get_chunk_from_payload(ptr);
	heap = search_heap(chunk);
	if (heap == NULL)
		return;
	if (chunk_is_corrupt(heap, chunk))
		return;
	set_chunk_free(chunk);
	t_config_type type = get_config_type(get_chunk_size(chunk));
	t_heap **head = get_arena_heap_head(type);
	merge_chunk(heap, chunk);
	if (heap->size - sizeof(t_heap) == get_chunk_size(chunk))
	{
		delete_heap(head, heap);
		release_some_memory((void *)heap, heap->size);
	}
}