#include "arena.h"
#include "config.h";

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

static void arena_unshift_new_tiny(t_config cfg)
{
	t_heap *tiny_head;

	tiny_head = get_arena_singletone()->tiny;
	return unshift_new_heap(&tiny_head, cfg);
}

static void arena_unshift_new_small(t_config cfg)
{
	t_heap *small_head;

	small_head = get_arena_singletone()->small;
	return unshift_new_heap(&small_head, cfg);
}

static void arena_unshift_new_large(t_config cfg)
{
	t_heap *large_head;

	large_head = get_arena_singletone()->large;
	return unshift_new_heap(&large_head, cfg);
}

extern void arena_unshift(t_config_type type)
{
	static void (*unshift[TYPES])(t_config config) =
		{
			[TINY] = &arena_unshift_new_tiny,
			[SMALL] = &arena_unshift_new_small,
			[LARGE] = &arena_unshift_new_large,
		};

	unshift[type](config(type));
}