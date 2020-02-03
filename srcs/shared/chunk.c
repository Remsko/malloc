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
	return get_chunk((void *)heap + sizeof(t_heap));
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
		// print_number("Splitted", (size_t)chunk + size);
		// print_number("NEXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXT", (size_t)get_next_chunk(chunk) + get_next_chunk(chunk)->forward);
	}
	return chunk;
}

inline bool chunk_is_available(t_chunk *chunk, size_t s)
{
	return chunk->free && s <= chunk->forward;
}

inline bool chunk_is_on_heap(t_heap *heap, t_chunk *chunk)
{
	void *start;
	void *end;

	start = (void *)heap;
	end = (void *)heap + heap->size;
	// print_number("start",(size_t)start);
	// print_number("end",(size_t)end);
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
		if (chunk_is_on_heap(heap, next) && next->free)
			chunk->forward += next->forward;
		else
			break;
	}
}

extern bool chunk_is_corrupt(t_heap *heap, t_chunk *search)
{
	t_chunk *compare;
	//int i;

	//print_string("ENDDDDDDDDDDDDDDDDDDDDDDDDD \n\n\n");

	compare = get_first_chunk(heap);
	while (chunk_is_on_heap(heap, compare))
	{
		if (compare == search)
		{
			return false;
		}
		compare = get_next_chunk(compare);
		// print_number("addr", (size_t)compare);
		// i=0;
		// while(i < 10000000)
		// 	i++;
	}
	return true;
}
