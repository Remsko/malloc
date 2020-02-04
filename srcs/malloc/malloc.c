#include "align.h"
#include "heap.h"
#include "config.h"
#include "arena.h"
#include "chunk.h"

t_chunk *get_free_chunk(size_t chunk_size)
{
	t_heap *heap;
	t_chunk *chunk;
	t_config_type type;
	size_t new_heap_size;

	type = get_config_type(chunk_size);
	if (type == LARGE)
	{
		new_heap_size = page_align(chunk_size + sizeof(t_heap));
		if (new_heap_size < chunk_size)
			return NULL;
	}
	else if ((chunk = search_free_chunk(type, chunk_size)))
	{
		split_chunk(chunk, type, chunk_size);
		return chunk;
	}
	else
		new_heap_size = get_heap_size(type);
	heap = arena_unshift(type, new_heap_size);
	if (heap == NULL)
		return NULL;
	chunk = get_first_chunk(heap);
	chunk->forward = heap->size - sizeof(t_heap);
	split_chunk(chunk, type, chunk_size);
	return chunk;
}

void *dynalloc(size_t size)
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
	set_chunk_used(chunk);
	payload = get_chunk_payload(chunk);
	return payload;
}

void *malloc(size_t size)
{
	void *ptr = dynalloc(size);
	return ptr;
}