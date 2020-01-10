#include "chunk.h"
#include "heap.h"
#include "config.h"
#include <stdbool.h>

inline t_chunk *get_chunk(void *start)
{
	return (t_chunk *)start;
}

inline t_chunk *new_chunk(void *start, size_t size)
{
	t_chunk *chunk;

	chunk = get_chunk(start);
	chunk->forward = size;
	chunk->free = true;
	return chunk;
}

inline t_chunk *get_chunk_from_payload(void *payload)
{
	return get_chunk(payload - sizeof(t_chunk));
}

inline t_chunk *get_next_chunk(t_chunk *chunk)
{
	return get_chunk((void *)chunk + chunk->forward);
}

inline void *get_chunk_payload(t_chunk *chunk)
{
	return (void *)chunk + sizeof(t_chunk);
}

inline size_t get_payload_size(t_chunk *chunk)
{
	return chunk->forward - sizeof(t_chunk);
}

inline t_chunk *get_first_chunk(t_heap *heap)
{
	return (void *)heap;
}

extern t_chunk *split_chunk_forward(t_heap *heap, t_chunk *chunk, t_config_type type)
{
	(void)heap;
	(void)chunk;
	// get heap size
	// get full size of the chunk
	// if chunk size > (2 * chunkheader size) + size + minchunksize
	if ((2 * sizeof(t_chunk)) + size + )
	// 		Process splitting
	//		*chunk = newheaderchunk
	//		chunk += headerchunk size + size
	//		*chunk = new header free chunk

	// return chunkStartPointer


	return NULL;
}

extern t_chunk *search_free_chunk(t_config_type type, size_t size)
{
	(void)type;
	(void)size;

	return NULL;
}