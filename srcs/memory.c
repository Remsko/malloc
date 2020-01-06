#include "incs/malloc.h"

/*
**
** MEMORY: [CHUNK1]->[CHUNK2]->[...]->NULL
**
*/

t_memory *get_memory_singletone(void)
{
	static t_memory m = (t_memory){0};

	return &m;
}

t_chunk_metadata *push_memory_chunk(t_chunk_metadata *cm)
{
	t_memory *memory;

	memory = memory_singletone();
	cm->next = memory->all;
	memory->all = cm;
	return cm;
}

t_chunk_metadata *push_new_memory_chunk(void *alloc, size_t alloc_size)
{
	t_chunk_metadata *cm;

	cm = new_chunk_metadata(alloc, alloc_size);
	return push_memory_chunk(cm);
}