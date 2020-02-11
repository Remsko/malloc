#include "heap.h"
#include "chunk.h"
#include "arena.h"
#include "malloc.h"
#include "libc.h"

// t_heap *search_heap(t_chunk *chunk, t_config_type *h_type)
// {
// 	t_heap **heap[TYPES];
// 	t_heap *h;
// 	bool not_finished;

// 	for (t_config_type type = 0; type < TYPES; type++)
// 		heap[type] = get_arena_heap_head(type);
// 	not_finished = true;
// 	while (not_finished)
// 	{
// 		not_finished = false;
// 		for (t_config_type type = 0; type < TYPES; type++)
// 		{
// 			h = *(heap[type]);
// 			if (h != NULL)
// 			{
// 				not_finished = true;
// 				if (chunk_is_on_heap(h, chunk))
// 				{
// 					*h_type = type;
// 					return h;
// 				}
// 				heap[type] = &h->next;
// 			}
// 		}
// 	}
// 	return NULL;
// }

t_chunk *search_free_chunk(t_heap *heap, size_t size)
{
    t_chunk *chunk;

    chunk = get_first_chunk(heap);
    while (chunk_is_on_heap(heap, chunk))
    {
        if (chunk_is_available(chunk, size))
        {
            split_chunk(heap, chunk, size);
            return chunk;
        }
        chunk = get_next_chunk(chunk);
    }
    return NULL;
}

t_chunk *search_free_chunk_disorder(t_heap *heap, size_t size)
{
    t_chunk *chunk;

    if (heap == NULL)
        return NULL;
    if ((chunk = search_free_chunk_disorder(heap->right, size)))
        return chunk;
    if ((chunk = search_free_chunk(heap, size)))
        return chunk;
    if ((chunk = search_free_chunk_disorder(heap->left, size)))
        return chunk;
    return NULL;
}

// bool search_heap_in_heaps(t_chunk *chunk, t_heap ***head_fnd, t_heap **heap_fnd)
// {
// 	t_heap **heap[TYPES];
// 	t_heap *h;
// 	bool not_finished;

// 	for (t_config_type type = 0; type < TYPES; type++)
// 		heap[type] = get_arena_heap_head(type);
// 	not_finished = true;
// 	while (not_finished)
// 	{
// 		not_finished = false;
// 		for (t_config_type type = 0; type < TYPES; type++)
// 		{
// 			h = *(heap[type]);
// 			if (h != NULL)
// 			{
// 				not_finished = true;
// 				if (chunk_is_on_heap(h, chunk))
// 				{
// 					*head_fnd = heap[type];
// 					*heap_fnd = h;
// 					return true;
// 				}
// 				heap[type] = &h->next;
// 			}
// 		}
// 	}
// 	return false;
// }

int chunk_cmp(t_chunk *chunk, void *heap)
{
    void *start;
    void *end;

    start = heap;
    end = heap + ((t_heap *)heap)->size;
    if ((void *)chunk < start)
        return -1;
    else if ((void *)chunk > end)
        return 1;
    else
        return 0;
}

bool search_chunk(t_chunk *chunk, t_heap ***head_fnd, t_heap **heap_fnd)
{
    t_heap **heap_head;
    t_heap *heap_maybe;

    for (t_config_type type = 0; type < TYPES; type++)
    {
        heap_head = get_arena_heap_head(type);
        if (heap_head != NULL)
        {
            heap_maybe = (t_heap *)rb_tree_heap_chunk_search((t_rb_tree *)*heap_head, chunk, &chunk_cmp);
            if (heap_maybe != NULL)
            {
                if (chunk_is_on_heap(heap_maybe, chunk))
                {
                    *head_fnd = heap_head;
                    *heap_fnd = heap_maybe;
                    return true;
                }
            }
        }
    }
    return false;
}