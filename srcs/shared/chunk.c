#include "chunk.h"
#include "heap.h"
#include "arena.h"
#include "config.h"
#include "debug.h"
#include <stdbool.h>

inline void set_chunk_free(t_chunk *chunk)
{
	chunk->forward |= FLAG_FREE;
}

inline void set_chunk_used(t_chunk *chunk)
{
	chunk->forward &= ~FLAG_FREE;
}

inline bool is_chunk_free(t_chunk *chunk)
{
	return (bool)(chunk->forward & FLAG_FREE);
}

inline t_chunk *get_chunk(void *start)
{
	return (t_chunk *)start;
}

inline t_chunk *new_chunk(void *start, size_t size)
{
	t_chunk *chunk;

	chunk = get_chunk(start);
	chunk->forward = size;
	set_chunk_free(chunk);
	return chunk;
}

inline size_t get_chunk_size(t_chunk *chunk)
{
	return chunk->forward & ~16U;
}

inline t_chunk *get_chunk_from_payload(void *payload)
{
	return get_chunk(payload - sizeof(t_chunk));
}

inline t_chunk *get_next_chunk(t_chunk *chunk)
{
	return get_chunk((void *)chunk + get_chunk_size(chunk));
}

inline void *get_chunk_payload(t_chunk *chunk)
{
	return (void *)chunk + sizeof(t_chunk);
}

inline size_t get_payload_size(t_chunk *chunk)
{
	return get_chunk_size(chunk) - sizeof(t_chunk);
}

inline t_chunk *get_first_chunk(t_heap *heap)
{
	return get_chunk((void *)heap + sizeof(t_heap));
}

#include <assert.h>
extern t_chunk *split_chunk(t_chunk *chunk, t_config_type type, size_t size)
{
	t_config config;
	size_t rest;

	assert(size <= get_chunk_size(chunk));
	config = get_config(type);
	rest = get_chunk_size(chunk) - size;
	if (sizeof(t_chunk) + config.chunk_min <= rest)
	{
		new_chunk((void *)chunk, size);
		new_chunk((void *)chunk + size, rest);
	}
	return chunk;
}

inline bool chunk_is_available(t_chunk *chunk, size_t s)
{
	return is_chunk_free(chunk) && s <= get_chunk_size(chunk);
}

inline bool chunk_is_on_heap(t_heap *heap, t_chunk *chunk)
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
	if (heap == NULL)
		return NULL;
	while ((*heap) != NULL)
	{
		chunk = get_first_chunk(*heap);
		while (chunk_is_on_heap(*heap, chunk))
		{
			if (chunk_is_available(chunk, size))
				return chunk;
			chunk = get_next_chunk(chunk);
		}
		heap = &(*heap)->next;
	}
	return NULL;
}

extern void merge_chunk(t_heap *heap, t_chunk *chunk)
{
	t_chunk *next;

	while (1)
	{
		next = get_next_chunk(chunk);
		if (chunk_is_on_heap(heap, next) && is_chunk_free(next))
			chunk->forward += get_chunk_size(next);
		else
			break;
	}
}

extern bool chunk_is_corrupt(t_heap *heap, t_chunk *search)
{
	t_chunk *compare;

	compare = get_first_chunk(heap);
	while (chunk_is_on_heap(heap, compare))
	{
		if (compare == search)
			return false;
		compare = get_next_chunk(compare);
	}
	return true;
}
