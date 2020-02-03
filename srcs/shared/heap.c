#include "heap.h"
#include "config.h"
#include "chunk.h"
#include "arena.h"

inline t_heap *get_heap(void *memory)
{
	return (t_heap *)memory;
}

inline t_heap *new_heap(void *memory, size_t size)
{
	t_heap *heap;

	heap = get_heap(memory);
	heap->size = size;
	return heap;
}

extern void delete_heap(t_heap **head, t_heap *delete)
{
	while ((*head) != delete)
		head = &(*head)->next;
	*head = delete->next;
}

inline t_heap *unshift_heap(t_heap **head, t_heap *new)
{
	new->next = (*head);
	(*head) = new;
	return new;
}

inline t_heap *unshift_new_heap(t_heap **head, void *memory, size_t size)
{
	t_heap *new;

	new = new_heap(memory, size);
	return unshift_heap(head, new);
}

extern size_t get_heap_size(t_config_type type)
{
	t_config config;

	config = get_config(type);
	return config.heap_size;
}

#include "debug.h"
extern t_heap *search_heap(t_chunk *chunk)
{
	t_heap **heap[TYPES];
	t_config_type type;
	bool forward;

	for (type = 0; type < TYPES; type++)
		heap[type] = get_arena_heap_head(type);
	forward = true;
	while (forward == true)
	{
		forward = false;
		for (type = 0; type < TYPES; type++)
		{
			if (*heap[type])
			{
				forward = true;
				if (chunk_is_on_heap(*heap[type], chunk))
					return *heap[type];
				heap[type] = &(*heap[type])->next;
			}
		}
	}
	return NULL;
}