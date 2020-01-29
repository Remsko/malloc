#include "chunk.h"
#include "heap.h"
#include "arena.h"
#include "config.h"
#include <stdbool.h>

inline t_chunk *get_chunk(void *start)
{
	return (t_chunk *)start;
}

inline t_chunk *new_chunk(void *start, size_t size)
{
	t_chunk *chunk;

	chunk = get_chunk(start);
	chunk->forward = size;
	chunk->free = true;
	return chunk;
}

inline t_chunk *get_chunk_from_payload(void *payload)
{
	return get_chunk(payload - sizeof(t_chunk));
}

inline t_chunk *get_next_chunk(t_chunk *chunk)
{
	return get_chunk((void *)chunk + chunk->forward);
}

inline void *get_chunk_payload(t_chunk *chunk)
{
	return (void *)chunk + sizeof(t_chunk);
}

inline size_t get_payload_size(t_chunk *chunk)
{
	return chunk->forward - sizeof(t_chunk);
}

inline t_chunk *get_first_chunk(t_heap *heap)
{
	return (void *)heap + sizeof(t_heap);
}

<<<<<<< Updated upstream
#include <assert.h>
=======
#include "debug.h"
>>>>>>> Stashed changes
extern t_chunk *split_chunk(t_chunk *chunk, t_config_type type, size_t size)
{
	t_config config;
	size_t rest;

<<<<<<< Updated upstream
	assert(size <= chunk->forward);
=======
	//print_number("size", size);
	//print_number("chunk", chunk->forward);
>>>>>>> Stashed changes
	config = get_config(type);
	rest = chunk->forward - size;
	if (sizeof(t_chunk) + config.chunk_min <= rest)
	{
		//print_number("rest", size);
		new_chunk((void *)chunk, size);
		new_chunk((void *)chunk + size, rest);
	}
	return chunk;
}

inline bool chunk_is_available(t_chunk *chunk, size_t s)
{
	return chunk->free && s <= chunk->forward;
}

#include <unistd.h>
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
#include <string.h>
bool chunk_is_on_heap(t_heap *heap, t_chunk *chunk)
{
	void *start;
	void *end;

	start = (void *)heap;
	//write(1, "1: ", strlen("1: "));
	//putnbr((size_t)start);
	//write(1, "\n2: ", strlen("\n2: "));

	end = (void *)heap + heap->size;
	//putnbr((size_t)end);
	//write(1, "\n", strlen("\n"));
	return (void *)chunk > start && (void *)chunk < end;
}

#include <string.h>
#include <unistd.h>
extern t_chunk *search_free_chunk(t_config_type type, size_t size)
{
	t_heap **heap;
	t_chunk *chunk;

	write(1, "search; ", strlen("search; "));
	heap = get_arena_heap_head(type);
	while ((*heap) != NULL)
	{
		chunk = get_first_chunk(*heap);
		while (chunk_is_on_heap(*heap, chunk))
		{
			//putnbr(size);
			if (chunk_is_available(chunk, size))
			{
				write(1, "found !! ", strlen("found !! "));
				return chunk;
			}
			chunk = get_next_chunk(chunk);
		}
		heap = &(*heap)->next;
	}
	return NULL;
}
