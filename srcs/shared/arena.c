#include "arena.h"
#include "heap.h"
#include "config.h"
#include "align.h"
#include "memory.h"
#include "malloc.h"

t_rb_node g_nil = {0, 0, 0, 0, BLACK};

t_arena_tree *get_arena_singletone(void)
{
	static t_arena_tree arena =
		{{.root = (t_heap_node *)&g_nil, .nil = (t_heap_node *)&g_nil},
		 {.root = (t_heap_node *)&g_nil, .nil = (t_heap_node *)&g_nil},
		 {.root = (t_heap_node *)&g_nil, .nil = (t_heap_node *)&g_nil}};

	return &arena;
}

t_heap_tree *get_arena_heap_tree(t_config_type type)
{
	t_arena_tree *arena;

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

t_heap_tree *get_arena_heap_tree_by_size(size_t size)
{
	t_config_type type;

	type = get_config_type(size);
	return get_arena_heap_tree(type);
}

t_heap_node *arena_unshift(t_heap_tree *tree, size_t size)
{
	t_heap_node *new;
	void *memory;

	memory = get_some_memory(size);
	new = unshift_new_heap(tree, memory, size);
	return new;
}