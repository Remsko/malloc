#include "malloc.h"

void ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

void *calloc(size_t count, size_t size)
{
	void *ptr;
	size_t total;

	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	total = count * size;
	if (total / count != size)
		return NULL;
	ptr = malloc(count * size);
	if (ptr)
		ft_bzero(ptr, count * size);
	return ptr;
}