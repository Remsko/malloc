#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>
#include "../incs/malloc.h"

void free(void *ptr)
{
	void *allocation;

	if (ptr == NULL)
		return;
	allocation = ptr - sizeof(t_heap);
	if (munmap(allocation, ((t_heap *)allocation)->size) != 0)
	{
		perror("Could not munmap");
	}
}