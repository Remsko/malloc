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
	return (void *)heap;
}


extern t_chunk *split_chunk_forward(t_heap *heap, t_chunk *chunk)
{
	(void)heap;
	(void)chunk;
	return NULL;
}


inline bool		chunk_is_available(t_chunk *chunk, size_t s)
{
	return !(chunk->free) && chunk->forward <= s;
}

inline bool		chunk_is_on_heap(t_heap *heap, t_chunk *chunk)
{
	return ((void*)heap + heap->size > (void*)chunk);
}

extern t_chunk *search_free_chunk(t_config_type type, size_t size)
{
	t_heap 		*heap;
	t_chunk		*chunk;
	size_t		chunk_count;

	heap = *(get_arena_heap_head(type));
	while (heap)
	{
		chunk = get_first_chunk(heap);
		chunk_count = 1;
		while (!chunk_is_available(chunk, size))
		{
			chunk = get_next_chunk(chunk);
			if (!chunk_is_on_heap(heap, chunk))
				return NULL;
		}
		heap = heap->next;
	}
	return chunk;
}
