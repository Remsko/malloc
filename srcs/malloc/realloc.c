#include "chunk.h"
#include "align.h"
#include "malloc.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

void *realloc(void *ptr, size_t size)
{
	t_chunk *old_chunk;
	size_t old_chunk_size;

	t_chunk *new_chunk;
	size_t new_chunk_size;

	// Check entries
	if (ptr == NULL || size <= 0)
		return NULL;

	// Format datas
	old_chunk = get_chunk_from_payload(ptr);
	old_chunk_size = old_chunk->forward;

	new_chunk_size = memory_align(size + sizeof(t_chunk));
	// If the new size can but putted in the existing chunk, return the same ptr 
	if (new_chunk_size <= old_chunk_size)
		return ptr;

	// Malloc new chunk
	new_chunk = get_chunk_from_payload(malloc(new_chunk_size));

	// Copy old chunk's datas
	new_chunk = ft_memcpy((void *) new_chunk, (void *) old_chunk, old_chunk_size);
	new_chunk->forward = new_chunk_size;

	// Free old chunk
	free(old_chunk + sizeof(t_chunk));
	return NULL;
}