#include "malloc.h"

void *calloc(size_t count, size_t size)
{
	void *ptr;
	size_t total;

	total = count * size;
	if (total / size < count)
		return NULL;
	ptr = malloc(total);
	if (ptr)
		ft_bzero(ptr, total);
	return ptr;
}