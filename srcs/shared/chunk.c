#include "chunk.h"
#include "heap.h"
#include "arena.h"
#include "config.h"
#include "debug.h"
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

#include <assert.h>
extern t_chunk *split_chunk(t_chunk *chunk, t_config_type type, size_t size)
{
	t_config config;
	size_t rest;

	assert(size <= chunk->forward);
	config = get_config(type);
	rest = chunk->forward - size;
	if (sizeof(t_chunk) + config.chunk_min <= rest)
	{
		new_chunk((void *)chunk, size);
		new_chunk((void *)chunk + size, rest);
	}
	return chunk;
}

inline bool chunk_is_available(t_chunk *chunk, size_t s)
{
	return chunk->free && s <= chunk->forward;
}

bool chunk_is_on_heap(t_heap *heap, t_chunk *chunk)
{
	void *start;
	void *end;

	start = (void *)heap;
	end = (void *)heap + heap->size;
	return ((void *)chunk > start && (void *)chunk < end);
}

extern t_chunk *search_free_chunk(t_config_type type, size_t size)
{
	t_heap **heap;
	t_chunk *chunk;

	heap = get_arena_heap_head(type);
	while ((*heap) != NULL)
	{
		chunk = get_first_chunk(*heap);
		while (chunk_is_on_heap(*heap, chunk) && chunk->forward != 0)
		{
			if (chunk_is_available(chunk, size))
			{
				print_string(" ; found ! ; ");
				return chunk;
			}
			chunk = get_next_chunk(chunk);
		}
		heap = &(*heap)->next;
	}
	return NULL;
}
