#include "heap.h"
#include "chunk.h"
#include "arena.h"
#include "malloc.h"

t_heap *search_heap(t_chunk *chunk, t_config_type *h_type)
{
	t_heap **heap[TYPES];
	t_heap *h;
	bool not_finished;

	for (t_config_type type = 0; type < TYPES; type++)
		heap[type] = get_arena_heap_head(type);
	not_finished = true;
	while (not_finished)
	{
		not_finished = false;
		for (t_config_type type = 0; type < TYPES; type++)
		{
			h = *(heap[type]);
			if (h != NULL)
			{
				not_finished = true;
				if (chunk_is_on_heap(h, chunk))
				{
					*h_type = type;
					return h;
				}
				heap[type] = &h->next;
			}
		}
	}
	return NULL;
}

t_chunk *search_free_chunk(t_heap **head, size_t size)
{
	t_chunk *chunk;

	if (head != NULL)
	{
		while ((*head) != NULL)
		{
			chunk = get_first_chunk(*head);
			while (chunk_is_on_heap(*head, chunk))
			{
				if (chunk_is_available(chunk, size))
				{
					split_chunk(*head, chunk, size);
					return chunk;
				}
				chunk = get_next_chunk(chunk);
			}
			head = &(*head)->next;
		}
	}
	return NULL;
}

bool search_heap_in_heaps(t_chunk *chunk, t_heap ***head_fnd, t_heap **heap_fnd)
{
	t_heap **heap[TYPES];
	t_heap *h;
	bool not_finished;

	for (t_config_type type = 0; type < TYPES; type++)
		heap[type] = get_arena_heap_head(type);
	not_finished = true;
	while (not_finished)
	{
		not_finished = false;
		for (t_config_type type = 0; type < TYPES; type++)
		{
			h = *(heap[type]);
			if (h != NULL)
			{
				not_finished = true;
				if (chunk_is_on_heap(h, chunk))
				{
					*head_fnd = heap[type];
					*heap_fnd = h;
					return true;
				}
				heap[type] = &h->next;
			}
		}
	}
	return false;
}