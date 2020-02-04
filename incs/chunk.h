#ifndef CHUNK_H
#define CHUNK_H

#include "heap.h"
#include "config.h"
#include <stddef.h>
#include <stdbool.h>

#define FLAG_FREE (1 << 0)

typedef struct s_chunk
{
	size_t forward;
	size_t backward;
} t_chunk;

t_chunk *new_chunk(void *start, size_t size);
t_chunk *get_chunk(void *start);
t_chunk *get_chunk_from_payload(void *payload);
t_chunk *get_next_chunk(t_chunk *chunk);
t_chunk *get_first_chunk(t_heap *heap);
t_chunk *split_chunk(t_chunk *chunk, t_config_type type, size_t size);
t_chunk *search_free_chunk(t_config_type type, size_t size);

void *get_chunk_payload(t_chunk *chunk);

size_t get_payload_size(t_chunk *chunk);
size_t get_chunk_size(t_chunk *chunk);

void merge_chunk(t_heap *heap, t_chunk *chunk);
void set_chunk_free(t_chunk *chunk);
void set_chunk_used(t_chunk *chunk);

bool chunk_is_available(t_chunk *chunk, size_t s);
bool chunk_is_on_heap(t_heap *heap, t_chunk *chunk);
bool chunk_is_corrupt(t_heap *heap, t_chunk *search);
bool is_chunk_free(t_chunk *chunk);

t_heap *search_heap(t_chunk *chunk);

#endif
