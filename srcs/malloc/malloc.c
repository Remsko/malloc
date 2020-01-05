#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

int div_roundup(int a, int b)
{
	return (a + b - 1) / b;
}

void *new_memory_allocation(size_t allocation_size)
{
	void *allocation;

	allocation = mmap(NULL, allocation_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (allocation == MAP_FAILED)
	{
		perror("Could not mmap");
		return NULL;
	}
	return allocation;
}

void *malloc(size_t size)
{
	void *new_region;
	size_t required;
	int pagesize;
	int num_pages;

	write(1, "START\n", 7);
	pagesize = getpagesize();
	required = size + sizeof(size_t);
	num_pages = div_roundup(required, pagesize);
	new_region = new_memory_allocation(num_pages);
	if (new_region == NULL)
		return NULL;
	*(size_t *)new_region = required; // We use this to free() the right number of bytes
	write(1, "END\n", 4);
	return (new_region + sizeof(size_t));
}