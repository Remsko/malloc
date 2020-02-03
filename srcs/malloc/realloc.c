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
	t_chunk *old_chunk;
	size_t old_chunk_size;

	t_chunk *new_chunk;
	size_t new_chunk_size;

	// Check entries
	//print_number("starting", size);
	if (ptr == NULL)
		return malloc(size);
	if (size == 0)
	{
		free(ptr);
		return NULL;
	}

	// Format datas
	//print_string("before chunk\n");
	old_chunk = get_chunk_from_payload(ptr);
	t_heap *heap = search_heap(old_chunk);
	if (heap == NULL)
		return NULL;
	if (chunk_is_corrupt(heap, old_chunk))
		return NULL;
	old_chunk_size = old_chunk->forward;
	//print_string("after chunk\n");

	new_chunk_size = memory_align(size + sizeof(t_chunk));
	// If the new size can but putted in the existing chunk, return the same ptr
	if (new_chunk_size <= old_chunk_size)
		return ptr;

	// Malloc new chunk
	void *new = malloc(new_chunk_size);
	if (!new)
		return NULL;
	new_chunk = get_chunk_from_payload(new);

	// Copy old chunk's datas
	//print_number("size", new_chunk->forward);
	size_t copy_length = (old_chunk_size - sizeof(t_chunk) < size) ? (old_chunk_size - sizeof(t_chunk) < size) : size;
	// print_number("sizeof", sizeof(t_chunk));
	// print_number("old", old_chunk_size);
	// print_number("size", size);
	// print_number("copy", copy_length);

	new_chunk = ft_memmove((void *)new_chunk + sizeof(t_chunk), (void *)old_chunk + sizeof(t_chunk), copy_length);
	//print_number("size", new_chunk->forward);

	// new_chunk->forward = new_chunk_size;

	// Free old chunk
	// print_string("before free\n");
	free(old_chunk + sizeof(t_chunk));
	// print_string("after free\n");
	return get_chunk_payload(new_chunk);
}