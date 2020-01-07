#include "config.h"
#include <unistd.h>

inline size_t tiny_heap_size()
{
	return getpagesize() * 4;
}

inline size_t tiny_chunk_size()
{
	return tiny_heap_size() / 128;
}

static t_config config_tiny()
{
	return (t_config){
		.chunk_size = tiny_chunk_size(),
		.heap_size = tiny_heap_size(),
	};
}

inline size_t small_heap_size()
{
	return getpagesize() * 32;
}

inline size_t small_chunk_size()
{
	return small_heap_size() / 128;
}

static t_config config_small()
{
	return (t_config){
		.chunk_size = small_chunk_size(),
		.heap_size = small_heap_size(),
	};
}

static t_config config_large()
{
	return (t_config){0, 0};
}

extern t_config config(t_config_type type)
{
	static t_config (*get_config[TYPES])() =
		{
			[TINY] = &config_tiny,
			[SMALL] = &config_small,
			[LARGE] = &config_large,
		};

	return get_config[type]();
}