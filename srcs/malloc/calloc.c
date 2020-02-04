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

	print_number("c", (size_t)ptr);
	total = count * size;
	if (total / size < count)
		return NULL;
	ptr = malloc(total);
	if (ptr)
		ft_bzero(ptr, total);
	return ptr;
}