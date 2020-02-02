#include "chunk.h"
#include "malloc.h"
#include "arena.h"
#include "memory.h"

void merge_chunk(t_heap *heap, t_chunk *chunk)
{
	t_chunk *next;

	while (1)
	{
		next = get_next_chunk(chunk);
		if (chunk_is_on_heap(heap, next) && next->free)
			chunk->forward += next->forward;
		else
			break;
	}
}

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
	//check_chunk;
	chunk->free = true;
	t_config_type type = get_config_type(chunk->forward);
	t_heap **head = get_arena_heap_head(type);
	merge_chunk(heap, chunk);
	if (heap->size - sizeof(t_heap) == chunk->forward)
	{
		delete_heap(head, heap);
		//release_some_memory((void *)heap, heap->size);
	}
}