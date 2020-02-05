#include "heap.h"
#include "chunk.h"
#include "config.h"

static void show_chunk(t_chunk *chunk)
{
    //print chunk format;
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
            //print heap format;
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
    // print total format;
}