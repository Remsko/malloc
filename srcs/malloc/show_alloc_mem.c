#include "heap.h"
#include "chunk.h"
#include "config.h"
#include "arena.h"
#include <stdio.h>

static void show_chunk(t_chunk *chunk)
{
    if (!chunk_is_free(chunk))
        printf("0x%X - 0x%X : %zu octets\n", (unsigned int)chunk, (unsigned int)get_next_chunk(chunk), get_chunk_size(chunk));
}

static size_t show_heap_and_count(t_config_type type)
{
    t_heap **heap;
    t_chunk *chunk;
    size_t heap_type_total;

    heap_type_total = 0;
    heap = get_arena_heap_head(type);
    if (heap != NULL)
    {
        while ((*heap) != NULL)
        {
            printf("%s : 0x%X\n", config_type_to_string(type), (unsigned int)*heap);
            heap_type_total += (*heap)->size;
            chunk = get_first_chunk(*heap);
            while (chunk_is_on_heap(*heap, chunk))
            {
                show_chunk(chunk);
                chunk = get_next_chunk(chunk);
            }
            heap = &(*heap)->next;
        }
    }
    return heap_type_total;
}

void show_alloc_mem(void)
{
    size_t total;

    total = 0;
    for (t_config_type type = 0; type < TYPES; type++)
        total += show_heap_and_count(type);
    printf("Total : %zu octets\n", total);
}