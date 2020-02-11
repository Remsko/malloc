#ifndef ARENA_H
#define ARENA_H

#include "heap.h"
#include "config.h"

typedef struct s_arena
{
	t_heap *small;
	t_heap *tiny;
	t_heap *large;
} t_arena;

t_arena *get_arena_singletone(void);
t_heap **get_arena_heap_head(t_config_type type);
t_heap **get_arena_heap_by_size(size_t size);
t_heap *arena_unshift(t_heap **head, size_t size);

#endif