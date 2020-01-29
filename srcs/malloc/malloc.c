#include "align.h"
#include "heap.h"
#include "config.h"
#include "arena.h"
#include "chunk.h"
#include "debug.h"

#include <unistd.h>
#include <string.h>

static void putnbr(size_t size)
{
	if (size > 9)
	{
		putnbr(size / 10);
		putnbr(size % 10);
	}
	else
	{
		write(1, (char[1]){size + '0'}, 1);
	}
}

t_chunk *get_free_chunk(size_t size)
{
	t_heap *heap;
	t_chunk *chunk;
	t_config_type type;

	type = get_config_type(size);
	write(1, " type: ", strlen(" type: "));
	putnbr(type);
	write(1, " ", 1);
	if (type == LARGE)
	{
		;
	}
	else if ((chunk = search_free_chunk(type, size)))
	{
<<<<<<< Updated upstream
		split_chunk(chunk, type, size);
		return chunk;
	}
=======
		print_number("chunk found", size);
		return chunk;
	}
	//else
	//size = get_heap_size(type);

>>>>>>> Stashed changes
	heap = arena_unshift(type, size);
	if (heap == NULL)
		return NULL;
	chunk = get_first_chunk(heap);
	chunk->forward = heap->size - sizeof(t_heap);
	split_chunk(chunk, type, size);
	//putnbr(chunk->forward);
	return chunk;
}

void *malloc(size_t size)
{
	t_chunk *chunk;
	void *payload;
	size_t chunk_size;

	//write(1, "start; ", strlen("start; "));
	if (size == 0)
		return NULL;
<<<<<<< Updated upstream
	chunk_size = memory_align(size + sizeof(t_chunk));
	if (chunk_size < size)
		return NULL;
	chunk = get_free_chunk(chunk_size);
=======
	//size = memory_align(sizeof(t_chunk) + size);
	chunk = get_free_chunk(size);
>>>>>>> Stashed changes
	if (chunk == NULL)
		return NULL;
	chunk->free = false;
	payload = get_chunk_payload(chunk);
	return payload;
}