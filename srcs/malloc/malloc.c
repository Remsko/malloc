#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include "../incs/malloc.h"

#include <sys/resource.h>

void *mmap_wrapper(size_t allocation_size)
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

// void *add_heap(size_t size)
// {
// 	void *new_allocation;
// 	size_t total_required;
// 	size_t allocation_size;

// 	total_required = MEMORY_ALIGN(size + HEAP_SIZE);
// 	allocation_size = PAGE_ALIGN(total_required);
// 	if ((new_allocation = mmap_wrapper(allocation_size)) == NULL)
// 		return NULL;

// 	t_heap *heap = (t_heap *)new_allocation;
// 	heap->size = allocation_size;
// 	return new_allocation + sizeof(t_heap);
// }

void *malloc(size_t size)
{
	void *user_payload = NULL;

	(void)size;
	write(1, "START\n", 7);
	/*user_payload = add_heap(size);*/
	write(1, "END\n", 4);
	return user_payload;
}