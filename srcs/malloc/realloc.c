#include "chunk.h"
#include "align.h"

void *realloc(void *ptr, size_t size)
{
	t_chunk *old_chunk;
	size_t old_chunk_size;

	//t_chunk *new_chunk = NULL;
	size_t new_chunk_size;

	// Check entries
	if (ptr == NULL || size <= 0)
		return NULL;

	// Format datas
	old_chunk = get_chunk_from_payload(ptr);
	old_chunk_size = old_chunk->forward;

	new_chunk_size = memory_align(size + sizeof(t_chunk));
	if (new_chunk_size < size)
		return NULL;

	if (old_chunk_size > new_chunk_size)
	{
		return NULL;
	}

	// Malloc new chunk

	// Copy old chunk's datas

	// Free old chunk
	return NULL;
}