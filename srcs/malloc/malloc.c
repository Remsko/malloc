#include "align.h"
#include "heap.h"
#include "config.h"
#include "arena.h"
#include <sys/mman.h>

void *get_some_memory(size_t size)
{
	void *memory;

	memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (memory == MAP_FAILED)
		return NULL;
	return (memory);
}

#include "chunk.h"
t_chunk *get_free_chunk(size_t size)
{
	t_heap *heap;
	t_chunk *chunk;
	t_config_type type;

	type = get_config_type(size);
	if (type == LARGE)
		;
	else if ((chunk = search_free_chunk(type, size)))
		return chunk;
	heap = arena_unshift(type, size);
	chunk = get_first_chunk(heap);
	return split_chunk_forward(heap, chunk);
}

void *malloc(size_t size)
{
	t_chunk *chunk;
	void *payload;

	if (size == 0)
		return NULL;
	size = memory_align(size);
	chunk = get_free_chunk(size);
	payload = get_chunk_payload(chunk);
	return payload;
}