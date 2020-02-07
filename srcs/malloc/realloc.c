#include "chunk.h"
#include "align.h"
#include "malloc.h"
#include "libc.h"

void *realloc(void *ptr, size_t size)
{
	void *new;
	t_heap *heap;
	t_chunk *chunk;

	if (size == 0 || ptr == NULL)
	{
		free(ptr);
		return malloc(size);
	}
	chunk = get_chunk_from_payload(ptr);
	t_config_type type;
	if (!chunk_is_referenced(&heap, &type, chunk) || chunk_is_corrupt(heap, chunk))
		return NULL;
	if (size <= get_payload_size(chunk))
		return ptr;
	new = malloc(size);
	if (new != NULL)
		ft_memmove(new, get_chunk_payload(chunk), get_payload_size(chunk));
	free(ptr);
	return new;
}