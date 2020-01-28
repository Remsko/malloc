#include "align.h"
#include "heap.h"
#include "config.h"
#include "arena.h"
#include "chunk.h"

#include <unistd.h>
#include <string.h>
t_chunk *get_free_chunk(size_t size)
{
	t_heap *heap;
	t_chunk *chunk;
	t_config_type type;

	type = get_config_type(size);
	if (type != LARGE)
		size = page_align(size);
	else if ((chunk = search_free_chunk(type, size)))
	{
		write(1, "found\n", strlen("found\n"));
		return chunk;
	}
	else
		size = get_heap_size(type);
	write(1, "mmap; ", strlen("mmap; "));
	heap = arena_unshift(type, size);
	if (heap == NULL)
		return NULL;
	chunk = get_first_chunk(heap);
	chunk->forward = heap->size - sizeof(t_heap);
	write(1, "split; ", strlen("split; "));
	split_chunk(chunk, type, size);
	write(1, "splitted; ", strlen("splitted; "));
	return chunk;
}

int div_roundup(int a, int b)
{
	return (a + b - 1) / b;
}

#include <sys/mman.h>
void *malloc(size_t size)
{
	t_chunk *chunk = NULL;
	void *payload = NULL;

	write(1, "start; ", strlen("start; "));
	if (size == 0)
		return NULL;
	//size = memory_align(sizeof(t_chunk) + size);
	chunk = get_free_chunk(size);
	if (chunk == NULL)
		return NULL;
	chunk->free = false;
	payload = get_chunk_payload(chunk);
	return payload;
}