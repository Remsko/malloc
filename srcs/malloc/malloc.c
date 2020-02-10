#include "align.h"
#include "heap.h"
#include "config.h"
#include "arena.h"
#include "chunk.h"
#include "malloc.h"

t_chunk *get_free_chunk(t_heap **head, size_t chunk_size)
{
	t_heap *new_heap;
	size_t new_heap_size;
	t_chunk *chunk;

	if ((chunk = search_free_chunk(head, chunk_size)))
		return chunk;
	new_heap_size = get_heap_size(chunk_size);
	if (new_heap_size < chunk_size)
		return NULL;
	new_heap = arena_unshift(head, new_heap_size);
	if (new_heap == NULL)
		return NULL;
	chunk = init_chunk(new_heap);
	split_chunk(new_heap, chunk, chunk_size);
	return chunk;
}

void *dynalloc(size_t size)
{
	t_heap **head;
	t_chunk *chunk;
	void *payload;
	size_t chunk_size;

	if (size == 0)
		size = 1;
	chunk_size = memory_align(size + sizeof(t_chunk));
	if (chunk_size < size)
		return NULL;
	head = get_arena_heap_by_size(chunk_size);
	// thread lock
	chunk = get_free_chunk(head, chunk_size);
	// thread unlock
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