#include "arena.h"
#include "heap.h"
#include "memory.h"
#include "chunk.h"
#include "test.h"
#include "debug.h"

void test_search_chunk(void)
{
    // heap
    putstr("Search chunk: ");
    size_t size = get_heap_size(1);
    t_heap *heap = arena_unshift(1, size);

    // one chunk
    t_chunk *chunk = get_first_chunk(heap);
    chunk->forward = size - sizeof(t_heap);
    split_chunk(heap, chunk, 1, 256);

    putstr("\n");
    print_heap(heap);

    t_chunk *found = search_free_chunk(1, 80);
    (found == NULL) ? putstr(" NO") : putstr(" OK");
    split_chunk(heap, found, 1, 80);

    putstr("\n");
    print_heap(heap);

    // two chunk
    t_chunk *found2 = search_free_chunk(1, 80);
    (found2 == NULL) ? putstr(" NO") : putstr(" OK");
    split_chunk(heap, found2, 1, 80);

    t_chunk *found3 = search_free_chunk(1, 80);
    (found3 == NULL) ? putstr(" NO") : putstr(" OK");
    split_chunk(heap, found3, 1, 80);

    //size > max
    t_chunk *notf = search_free_chunk(1, size);
    (notf == NULL) ? putstr(" OK") : putstr(" NO");

    t_chunk *notf2 = search_free_chunk(1, size);
    (notf2 == NULL) ? putstr(" OK") : putstr(" NO");

    // size < min
    putstr("\n");
    print_heap(heap);
}