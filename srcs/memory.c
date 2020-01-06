#include <sys/mman.h>
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

void push_memory_chunk(t_chunk_metadata *cm)
{
	t_memory *memory;

	memory = memory_singletone();
	cm->next = memory->all;
	memory->all = cm;
}

void push_new_memory_chunk(void *alloc, size_t alloc_size)
{
	t_chunk_metadata *cm;

	cm = new_chunk_metadata(alloc, alloc_size);
	return push_memory_chunk(cm);
}

void *new_memory_allocation(size_t allocation_size)
{
	void *allocation;

	allocation = mmap(NULL, allocation_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (allocation == MAP_FAILED)
	{
		if (DEBUG)
			perror("Could not mmap");
		return NULL;
	}
	return (allocation);
}