#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>

void free(void *ptr)
{
	void *region = ptr - sizeof(size_t);
	if (munmap(region, *(size_t *)region) != 0)
	{
		perror("Could not munmap");
	}
}