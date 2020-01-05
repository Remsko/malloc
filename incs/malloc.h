#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#include <stdbool.h>

#define DEBUG 1

void *malloc(size_t size);
void free(void *ptr);

typedef struct s_chunk_metadata
{
	size_t total_size;
	struct s_chunk *next;
} t_chunk_metadata;

typedef struct s_block_header
{
	size_t total_size;
	bool free;
} t_block_header;

#define CHUNK_SIZE (sizeof(t_chunk_metadata))
#define BLOCK_HEADER_SIZE (sizeof(t_block_header))

#endif