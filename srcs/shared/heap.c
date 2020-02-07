#include "heap.h"
#include "config.h"
#include "chunk.h"
#include "arena.h"
#include "memory.h"

void delete_heap(t_heap **head, t_heap *delete)
{
	while ((*head) != delete)
		head = &(*head)->next;
	*head = delete->next;
}

void show_heap(t_heap *heap, t_config_type type);

void release_heap_maybe(t_heap *heap, t_config_type type)
{
	t_heap **head;
	t_chunk *chunk;

	chunk = get_first_chunk(heap);
	if (heap->size - sizeof(t_heap) == get_chunk_size(chunk))
	{
		head = get_arena_heap_head(type);
		delete_heap(head, heap);
		release_some_memory((void *)heap, heap->size);
	}
}

size_t get_heap_size(t_config_type type)
{
	t_config config;

	config = get_config(type);
	return config.heap_size;
}

t_heap *get_heap(void *memory)
{
	return (t_heap *)memory;
}

t_heap *new_heap(void *memory, size_t size)
{
	t_heap *heap;

	heap = get_heap(memory);
	heap->size = size;
	return heap;
}

t_heap *unshift_heap(t_heap **head, t_heap *new)
{
	new->next = (*head);
	(*head) = new;
	return new;
}

t_heap *unshift_new_heap(t_heap **head, void *memory, size_t size)
{
	t_heap *new;

	new = new_heap(memory, size);
	return unshift_heap(head, new);
}

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