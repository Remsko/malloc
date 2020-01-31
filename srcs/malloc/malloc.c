#include "align.h"
#include "heap.h"
#include "config.h"
#include "arena.h"
#include "chunk.h"
#include "debug.h"

t_chunk *get_free_chunk(size_t size)
{
	t_heap *heap;
	t_chunk *chunk;
	t_config_type type;
	size_t new_alloc;

	type = get_config_type(size);
	if (type == LARGE)
		new_alloc = size;
	else if ((chunk = search_free_chunk(type, size)))
	{
		split_chunk(chunk, type, size);
		return chunk;
	}
	else
		new_alloc = get_heap_size(type);
	heap = arena_unshift(type, new_alloc);
	if (heap == NULL)
		return NULL;
	chunk = get_first_chunk(heap);
	chunk->forward = heap->size - sizeof(t_heap);
	split_chunk(chunk, type, size);
	return chunk;
}

void *malloc(size_t size)
{
	t_chunk *chunk;
	void *payload;
	size_t chunk_size;

	if (size == 0)
		return NULL;
	chunk_size = memory_align(size + sizeof(t_chunk));
	if (chunk_size < size)
		return NULL;
	chunk = get_free_chunk(chunk_size);
	if (chunk == NULL)
		return NULL;
	chunk->free = false;
	payload = get_chunk_payload(chunk);
	return payload;
}