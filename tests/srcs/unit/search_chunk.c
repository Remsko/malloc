#include "arena.h"
#include "heap.h"
#include "memory.h"
#include "chunk.h"
#include "test.h"

void test_search_chunk(void)
{
    // heap
    putstr("Search chunk: ");
    size_t size = get_heap_size(1);
    putnbr(size);
    t_heap *heap = arena_unshift(1, size);

    // one chunk
    t_chunk *chunk = get_first_chunk(heap);
    chunk->forward = size - sizeof(t_heap);
    split_chunk(chunk, 1, 256);
    t_chunk *found = search_free_chunk(1, 80);
    (found == NULL) ? putstr(" NO") : putstr(" OK");
    split_chunk(found, 1, 80);

    // two chunk
    t_chunk *found2 = search_free_chunk(1, 80);
    (found2 == NULL) ? putstr(" NO") : putstr(" OK");
    split_chunk(found2, 1, 80);

    // three chunk
    t_chunk *found3 = search_free_chunk(1, 80);
    (found3 == NULL) ? putstr(" NO") : putstr(" OK");
    split_chunk(found3, 1, 80);
    putnbr(get_next_chunk(get_next_chunk(found3))->forward);

    // size > max
    t_chunk *notf = search_free_chunk(1, size - (2 * 80) - 256 + 1);
    putnbr(notf->forward);
    (notf == NULL) ? putstr("OK") : putstr(" NO");

    t_chunk *notf2 = search_free_chunk(1, size);
    putnbr(notf2->forward);
    (notf2 == NULL) ? putstr("OK") : putstr(" NO");
    // size < min
    putstr("\n");
}