#include "chunk.h"
#include "malloc.h"
#include "arena.h"
#include "memory.h"

#include "debug.h"
void free(void *ptr)
{
	t_heap *heap;
	t_chunk *chunk;

	if (ptr == NULL)
		return;
	chunk = get_chunk_from_payload(ptr);
	heap = search_heap(chunk);
	if (heap == NULL)
		return;
	// print_string("\n");
	// print_heap(heap);
	if (chunk_is_corrupt(heap, chunk))
		return;
	set_chunk_free(chunk);
	t_config_type type = get_config_type(get_chunk_size(chunk));
	chunk = merge_chunk(heap, chunk);
	//print_heap(heap);
	// print_string("\n");
	if (heap->size - sizeof(t_heap) == get_chunk_size(chunk))
	{
		//print_string("\nDELETE\n");
		delete_heap(get_arena_heap_head(type), heap);
		release_some_memory((void *)heap, heap->size);
	}
}