#include "align.h"
#include <sys/mman.h>

void *get_some_memory(size_t size)
{
	void *memory;

	memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (memory == MAP_FAILED)
		return NULL;
	return (memory);
}

void *malloc(size_t size)
{
	void *payload = NULL;

	if (size == 0)
		return NULL;
	return payload;
}