#include "../incs/malloc.h"

/*
** CHUNK:	[chunk_metadata][block_1][block_2][...]
**			----------------------------------------- alloc_size
**			----------------                          sizeof(t_chunk_metadata)
**							------------------------- total_blocks * block_size < alloc_size - sizeof(t_chunk_metadata)
*/

inline t_chunk_metadata *get_chunk_metadata(void *alloc)
{
	return (t_chunk_metadata *)alloc;
}

t_chunk_metadata *new_chunk_metadata(void *alloc, size_t alloc_size)
{
	t_chunk_metadata *chunk_metadata;

	chunk_metadata = get_chunk_metadata(alloc);
	chunk_metadata->total_size = alloc_size;
	return chunk_metadata;
}
