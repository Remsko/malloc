#include "heap.h"

inline t_heap *get_heap(void *alloc)
{
	return (t_heap *)alloc;
}

inline t_heap *new_heap(void *alloc, size_t alloc_size)
{
	t_heap *heap;

	heap = get_heap(alloc);
	heap->size = alloc_size;
	return heap;
}

inline t_heap *push_front_heap(t_heap **head, t_heap *new)
{
	new->next = (*head);
	(*head) = new;
	return new;
}

inline t_heap *push_front_new_heap(t_heap **head, void *alloc, size_t alloc_size)
{
	t_heap *new;

	new = new_heap(alloc, alloc_size);
	return push_heap(head, new);
}