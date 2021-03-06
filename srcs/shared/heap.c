#include "heap.h"
#include "config.h"
#include "chunk.h"
#include "arena.h"
#include "memory.h"
#include "align.h"

void delete_heap(t_heap **head, t_heap *delete)
{
	while ((*head) != delete)
		head = &(*head)->next;
	*head = delete->next;
}

void release_heap_maybe(t_heap **head, t_heap *heap)
{
	t_chunk *chunk;

	chunk = get_first_chunk(heap);
	if (heap->size - sizeof(t_heap) == get_chunk_size(chunk))
	{
		delete_heap(head, heap);
		release_some_memory((void *)heap, heap->size);
	}
}

size_t get_heap_size(size_t chunk_size)
{
	t_config config;
	t_config_type type;

	type = get_config_type(chunk_size);
	if (type == LARGE)
		return page_align(chunk_size + sizeof(t_heap));
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

t_heap *insert_heap(t_heap **head, t_heap *new)
{
	t_heap *current;

	if (*head == NULL || (void *)*head > (void *)new)
	{
		new->next = *head;
		*head = new;
	}
	else
	{
		current = *head;
		while (current->next != NULL && (void *)current->next < (void *)new)
			current = current->next;
		new->next = current->next;
		current->next = new;
	}
	return new;
}

t_heap *insert_new_heap(t_heap **head, void *memory, size_t size)
{
	t_heap *new;

	new = new_heap(memory, size);
	insert_heap(head, new);
	return new;
}
