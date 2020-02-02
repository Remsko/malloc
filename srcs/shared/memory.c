#include <sys/mman.h>
#include <stddef.h>
#include <assert.h>
#include "debug.h"

void *get_some_memory(size_t size)
{
	void *memory;

	memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (memory == MAP_FAILED)
		return NULL;
	print_number("\nout", (size_t)memory);
	print_number("with", size);
	return (memory);
}

void release_some_memory(void *memory, size_t size)
{
	//int ret;

	print_number("\nin", (size_t)memory);
	print_number("with", size);
	munmap(memory, size);
	//assert(ret != 0);
}