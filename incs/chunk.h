#ifndef CHUNK_H
#define CHUNK_H

#include <stddef.h>
#include <stdbool.h>

typedef struct s_chunk
{
	size_t forward;
	bool free;
} t_chunk;

#endif