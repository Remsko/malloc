#include <sys/mman.h>
#include <stddef.h>
#include <assert.h>

#include "debug.h"
//static size_t total = 0;

void *get_some_memory(size_t size)
{
	void *memory;

	//total += size;
	//print_number("total +", total);
	memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (memory == MAP_FAILED)
		return NULL;
	return (memory);
}

void release_some_memory(void *memory, size_t size)
{
	//total -= size;
	//print_number("total -", total);
	munmap(memory, size);
}