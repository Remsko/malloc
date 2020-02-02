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
	chunk->free = true;
	//merge_chunk(chunk);
	if (heap->size - sizeof(t_heap) == chunk->forward)
	{
		release_some_memory((void *)heap, heap->size);
	}
}