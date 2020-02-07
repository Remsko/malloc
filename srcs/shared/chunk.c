#include "chunk.h"
#include "align.h"
#include "arena.h"
#include <stdbool.h>

void set_chunk_free(t_chunk *chunk)
{
	chunk->forward |= FLAG_FREE;
}

void set_chunk_used(t_chunk *chunk)
{
	chunk->forward &= ~FLAG_FREE;
}

bool chunk_is_free(t_chunk *chunk)
{
	return (bool)(chunk->forward & FLAG_FREE);
}

t_chunk *get_chunk(void *start)
{
	return (t_chunk *)start;
}

t_chunk *new_chunk(void *start, size_t size)
{
	t_chunk *chunk;

	chunk = get_chunk(start);
	chunk->forward = size;
	set_chunk_free(chunk);
	return chunk;
}

size_t get_chunk_size(t_chunk *chunk)
{
	return chunk->forward & ~(MEMORY_ALIGNMENT - 1);
}

t_chunk *get_chunk_from_payload(void *payload)
{
	return get_chunk(payload - sizeof(t_chunk));
}

t_chunk *get_next_chunk(t_chunk *chunk)
{
	return get_chunk((void *)chunk + get_chunk_size(chunk));
}

t_chunk *get_previous_chunk(t_chunk *chunk)
{
	return get_chunk((void *)chunk - chunk->backward);
}

void *get_chunk_payload(t_chunk *chunk)
{
	return (void *)chunk + sizeof(t_chunk);
}

size_t get_payload_size(t_chunk *chunk)
{
	return get_chunk_size(chunk) - sizeof(t_chunk);
}

t_chunk *get_first_chunk(t_heap *heap)
{
	return get_chunk((void *)heap + sizeof(t_heap));
}

void update_next_chunk(t_heap *heap, t_chunk *chunk)
{
	t_chunk *next;

	next = get_next_chunk(chunk);
	if (chunk_is_on_heap(heap, next))
		next->backward = get_chunk_size(chunk);
}

#include <assert.h>
t_chunk *split_chunk(t_heap *heap, t_chunk *chunk, t_config_type type, size_t size)
{
	t_chunk *new;
	t_config config;
	size_t rest;

	assert(size <= get_chunk_size(chunk));
	config = get_config(type);
	rest = get_chunk_size(chunk) - size;
	if (sizeof(t_chunk) + config.chunk_min <= rest)
	{
		new_chunk((void *)chunk, size);
		new = new_chunk((void *)chunk + size, rest);
		new->backward = size;
		update_next_chunk(heap, new);
	}
	return chunk;
}

bool chunk_is_available(t_chunk *chunk, size_t s)
{
	return chunk_is_free(chunk) && s <= get_chunk_size(chunk);
}

bool chunk_is_on_heap(t_heap *heap, t_chunk *chunk)
{
	void *start;
	void *end;

	start = (void *)heap;
	end = (void *)heap + heap->size;
	return ((void *)chunk > start && (void *)chunk < end);
}

#include "debug.h"
t_chunk *search_free_chunk(t_config_type type, size_t size)
{
	t_heap **heap;
	t_chunk *chunk;

	heap = get_arena_heap_head(type);
	if (heap != NULL)
	{
		while ((*heap) != NULL)
		{
			chunk = get_first_chunk(*heap);
			while (chunk_is_on_heap(*heap, chunk))
			{
				//print_number("chk", (size_t)chunk);
				if (chunk_is_available(chunk, size))
				{
					split_chunk(*heap, chunk, type, size);
					return chunk;
				}
				chunk = get_next_chunk(chunk);
			}
			heap = &(*heap)->next;
		}
	}
	return NULL;
}

static t_chunk *merge_chunk(t_chunk *start, t_chunk *end)
{
	start->forward += get_chunk_size(end);
	return start;
}

void show_chunk(t_chunk *chunk);

t_chunk *coalesce_chunk(t_heap *heap, t_chunk *chunk)
{
	t_chunk *next;
	t_chunk *prev;
	bool coalescion;

	//print_string("\n[MERGING]\n");
	coalescion = false;
	next = get_next_chunk(chunk);
	//show_chunk(next);
	//print_number("next heap", chunk_is_on_heap(heap, next));
	//print_number("next free", chunk_is_free(next));
	//show_chunk(chunk);
	//print_number("chk prev", chunk->backward);
	if (chunk_is_on_heap(heap, next) && chunk_is_free(next) && next != chunk)
	{
		//print_string("[MERGE AFTER]");
		coalescion = true;
		merge_chunk(chunk, next);
	}
	prev = get_previous_chunk(chunk);
	//show_chunk(prev);
	//print_number("prev heap", chunk_is_on_heap(heap, prev));
	//print_number("prev free", chunk_is_free(prev));
	//print_number("prev !chunk", prev != chunk);
	if (chunk_is_on_heap(heap, prev) && chunk_is_free(prev) && prev != chunk)
	{
		//print_string("[MERGE BEFORE]");
		coalescion = true;
		chunk = merge_chunk(prev, chunk);
	}
	if (coalescion)
		update_next_chunk(heap, chunk);
	//print_string("\n\n");
	return chunk;
}

bool chunk_is_corrupt(t_heap *heap, t_chunk *search)
{
	t_chunk *compare;

	if (heap == NULL)
		return true;
	compare = get_first_chunk(heap);
	while (chunk_is_on_heap(heap, compare))
	{
		if (compare == search)
			return false;
		compare = get_next_chunk(compare);
	}
	return true;
}

bool chunk_is_referenced(t_heap **heap, t_config_type *type, t_chunk *chunk)
{
	*heap = search_heap(chunk, type);
	return *heap != NULL;
}