#include "chunk.h"
#include "align.h"
#include "malloc.h"

void *ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	if (src <= dest)
		while (n--)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	else
		ft_memcpy(dest, src, n);
	return ((void *)dest);
}

void *realloc(void *ptr, size_t size)
{
	void *new;
	t_heap *heap;
	t_chunk *chunk;

	if (size == 0 || ptr == NULL)
	{
		new = malloc(size);
		free(ptr);
		return new;
	}
	chunk = get_chunk_from_payload(ptr);
	if (!chunk_is_referenced(&heap, chunk) || chunk_is_corrupt(heap, chunk))
		return NULL;
	if (size <= get_payload_size(chunk))
		return ptr;
	new = malloc(size);
	if (new != NULL)
		ft_memmove(new, get_chunk_payload(chunk), get_payload_size(chunk));
	free(ptr);
	return new;
}