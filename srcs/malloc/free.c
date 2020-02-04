#include "chunk.h"
#include "malloc.h"
#include "arena.h"
#include "memory.h"
#include "debug.h"

void free(void *ptr)
{
	t_heap *heap;
	t_chunk *chunk;

	print_number("f", (size_t)ptr);
	if (ptr == NULL)
	{
		print_string("last\n");
		return;
	}
	chunk = get_chunk_from_payload(ptr);
	heap = search_heap(chunk);
	if (heap == NULL)
	{
		return;
	}
	if (chunk_is_corrupt(heap, chunk))
	{
		return;
	}
	chunk->free = true;
	t_config_type type = get_config_type(chunk->forward);
	t_heap **head = get_arena_heap_head(type);
	merge_chunk(heap, chunk);
	if (heap->size - sizeof(t_heap) == chunk->forward)
	{
		delete_heap(head, heap);
		release_some_memory((void *)heap, heap->size);
	}
}