#include "arena.h"
#include "config.h";

inline t_arena *get_arena_singletone(void)
{
	static t_arena arena =
		(t_arena){
			.tiny = NULL,
			.small = NULL,
			.large = NULL,
		};

	return &arena;
}

void push_front_tiny(size_t request)
{
	t_config config_tiny;

	config_tiny = config()[TINY];
}

void push_front_small(size_t request)
{
	t_config config_small;

	config_small = config()[SMALL];
}

void push_front_large(size_t request)
{
}

inline void arena_push_front_to(t_config_type type, size_t request)
{
	static void (*push_front[TYPES])() =
		{
			[TINY] = &push_front_tiny,
			[SMALL] = &push_front_small,
			[LARGE] = &push_front_large,
		};

	push_front[type](request);
}