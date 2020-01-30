#include "heap.h"
#include "config.h"

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

#include "debug.h"
extern size_t get_heap_size(t_config_type type)
{
	t_config config;

	config = get_config(type);
	return config.heap_size;
}

#include "chunk.h"
extern void print_heap(t_heap *heap)
{
	t_chunk *chunk;

	print_string("heap(");
	ft_putnbr(heap->size);
	print_string("): ");
	ft_putnbr((size_t)heap);
	print_string("|");
	ft_putnbr((size_t)((size_t)heap + heap->size));
	print_string(";");
	chunk = get_first_chunk(heap);
	ft_putnbr((size_t)chunk);
	print_string("(");
	ft_putnbr(chunk->forward);
	print_string("-");
	ft_putnbr(chunk->free);
	print_string(")");
	chunk = get_next_chunk(chunk);
	while (chunk_is_on_heap(heap, chunk))
	{
		print_string("->");
		print_string("[");
		ft_putnbr(chunk_is_on_heap(heap, chunk));
		print_string("]");
		ft_putnbr((size_t)chunk);
		print_string("(");
		ft_putnbr(chunk->forward);
		print_string("-");
		ft_putnbr(chunk->free);
		print_string(")");
		chunk = get_next_chunk(chunk);
	}
	ft_putnbr((size_t)chunk);
	// print_string("(");
	// ft_putnbr(chunk->forward);
	// print_string(")");
	print_string("\n");
}