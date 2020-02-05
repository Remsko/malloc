#include "test.h"
#include "heap.h"
#include "chunk.h"
#include "arena.h"
#include "debug.h"

void test_search_heap(void)
{
	putstr("Search Heap:");
	t_heap *heap = arena_unshift(2, 4096);
	t_chunk *chunk = get_first_chunk(heap);
	chunk->forward = heap->size - sizeof(t_heap);
	split_chunk(heap, chunk, 2, 2048);

	t_heap *found1 = search_heap(chunk);
	t_chunk *chunk2 = get_next_chunk(chunk);
	t_heap *found2 = search_heap(chunk2);
	(found1) ? putstr(" OK") : putstr(" NO");
	(found2) ? putstr(" OK") : putstr(" NO");
	putstr("\n");
}