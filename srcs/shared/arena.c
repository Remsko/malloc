#include "arena.h"
#include "heap.h"
#include "config.h"
#include "align.h"
#include "memory.h"
#include <assert.h>

extern t_arena *get_arena_singletone(void)
{
	static t_arena arena =
		(t_arena){
			.tiny = NULL,
			.small = NULL,
			.large = NULL,
		};

	return &arena;
}

extern t_heap **get_arena_heap_head(t_config_type type)
{
	t_arena *arena;

	arena = get_arena_singletone();
	switch (type)
	{
	case TINY:
		return &arena->tiny;
	case SMALL:
		return &arena->small;
	case LARGE:
		return &arena->large;
	default:
		return NULL;
	}
}

extern t_heap *arena_unshift(t_config_type type, size_t size)
{
	t_heap **head;
	void *memory;
	size_t total;

	total = size + sizeof(t_heap);
	if (total < size)
		return NULL;
	memory = get_some_memory(total);
	head = get_arena_heap_head(type);
	if (memory == NULL || head == NULL)
		return NULL;
	return unshift_new_heap(head, memory, total);
}