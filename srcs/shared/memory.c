#include <sys/mman.h>
#include <stddef.h>

void *get_some_memory(size_t size)
{
	void *memory;

	memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (memory == MAP_FAILED)
		return NULL;
	return (memory);
}
