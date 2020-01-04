#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>

int div_roundup(int a, int b)
{
	return (a + b - 1) / b;
}

// void *new_memory_allocation(size_t allocation_size)
// {
// 	void *allocation = mmap(NULL, allocation_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

// 	if (allocation == MAP_FAILED)
// 	{
// 		return NULL;
// 	}
// 	return allocation;
// }

void *malloc(size_t size)
{
	int pagesize = getpagesize();
	size_t required = size + sizeof(size_t);
	int num_pages = div_roundup(required, pagesize);
	void *new_region = mmap(0, num_pages, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (new_region == MAP_FAILED)
	{
		perror("Could not mmap");
		return NULL;
	}
	*(size_t *)new_region = required; // We use this to free() the right number of bytes
	return new_region + sizeof(size_t);
}