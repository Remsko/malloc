#include "chunk.h"
#include "malloc.h"
#include "arena.h"

void show_chunk(t_chunk *chunk);

#include <stdio.h>
void free(void *ptr)
{
	t_heap *heap;
	t_chunk *chunk;
	t_config_type type;

	if (ptr == NULL)
		return;
	chunk = get_chunk_from_payload(ptr);
	if (!chunk_is_referenced(&heap, &type, chunk) || chunk_is_corrupt(heap, chunk))
		return;
	set_chunk_free(chunk);
	chunk = coalesce_chunk(heap, chunk);
	release_heap_maybe(heap, type);
}
