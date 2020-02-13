#include "heap.h"
#include "chunk.h"
#include "arena.h"
#include "malloc.h"
#include "libc.h"

t_chunk *search_free_chunk(t_heap *heap, size_t size)
{
    t_chunk *chunk;

    if (heap == NULL)
        return NULL;
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
#include "debug.h"
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

int chunk_cmp(t_chunk *chunk, void *heap)
{
    if ((void *)chunk < heap)
        return -1;
    else if ((void *)chunk > (heap + ((t_heap *)heap)->size))
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