#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include "../incs/malloc.h"

#include <sys/resource.h>

#define ALIGN(size, alignment) (((size) + (alignment - 1)) & ~(alignment - 1))

#define MEMORY_ALIGNMENT (16)
#define MEMORY_ALIGN(size) (ALIGN(size, MEMORY_ALIGNMENT))

#define PAGE_SIZE (getpagesize())
#define PAGE_ALIGN(size) (ALIGN(size, PAGE_SIZE))

void *add_chunk(size_t size)
{
	void *new_allocation;
	size_t total_required;
	size_t allocation_size;

	total_required = MEMORY_ALIGN(size + CHUNK_SIZE);
	allocation_size = PAGE_ALIGN(total_required);
	if ((new_allocation = new_memory_allocation(allocation_size)) == NULL)
		return NULL;

	t_chunk_metadata *chunk = (t_chunk_metadata *)new_allocation;
	chunk->total_size = allocation_size;
	return new_allocation + sizeof(t_chunk_metadata);
}

void *malloc(size_t size)
{
	void *user_payload;

	write(1, "START\n", 7);
	user_payload = add_chunk(size);
	write(1, "END\n", 4);
	return user_payload;
}