#include "chunk.h"
#include "align.h"
#include "malloc.h"
#include "debug.h"

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

	if (!size)
	{
		free(ptr);
		return NULL;
	}
	if (!ptr)
	{
		return malloc(size);
	}
	t_chunk *chunk = get_chunk_from_payload(ptr);
	t_heap *heap = search_heap(chunk);
	if (!heap)
		return NULL;
	if (chunk_is_corrupt(heap, chunk))
		return NULL;
	if (size < chunk->forward - sizeof(t_chunk))
		return ptr;
	void *new = malloc(size);
	if (!new)
		return NULL;
	ft_memcpy(new, get_chunk_payload(chunk), chunk->forward - sizeof(t_chunk));
	return new;
}