#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

#define ALIGN(size, alignment) (((size) + (alignment - 1)) & ~(alignment - 1))

#define MEMORY_ALIGNMENT (1 << 4)
#define MEMORY_ALIGN(size) ALIGN(size, MEMORY_ALIGNMENT)

#define CHUNK_SIZE (1 << 14)
#define CHUNK_ALIGN(size) ALIGN(size, CHUNK_SIZE)

typedef struct s_header
{
	size_t block_size;
} t_header;

#define HEADER_SIZE sizeof(t_header)

void *new_memory_allocation(size_t allocation_size)
{
	void *allocation;

	allocation = mmap(NULL, allocation_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (allocation == MAP_FAILED)
	{
		perror("Could not mmap");
		return NULL;
	}
	return (allocation);
}

void fill_header_with_allocation_size(void *chunk, size_t chunk_size)
{
	*(size_t *)chunk = chunk_size; // We use this to free() the right number of bytes
}

void *get_user_payload(void *chunk, size_t header_size)
{
	return (chunk + header_size);
}

void *malloc(size_t size)
{
	void *new_allocation;
	size_t required;
	size_t allocation_size;

	write(1, "START\n", 7);
	required = MEMORY_ALIGN(size + HEADER_SIZE);
	allocation_size = CHUNK_ALIGN(required);
	if ((new_allocation = new_memory_allocation(allocation_size)) == NULL)
		return NULL;
	fill_header_with_allocation_size(new_allocation, required);
	write(1, "END\n", 4);

	return get_user_payload(new_allocation, HEADER_SIZE);
}