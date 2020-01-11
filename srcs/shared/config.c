#include "config.h"
#include <unistd.h>

static t_config config_tiny()
{
	size_t xpages;

	xpages = getpagesize() * 4;
	return (t_config){
		.heap_size = xpages,
		.chunk_min = 1,
		.chunk_max = xpages / 128,
	};
}

static t_config config_small()
{
	size_t xpages;

	xpages = getpagesize() * 32;
	return (t_config){
		.heap_size = xpages,
		.chunk_min = (xpages / 8) / 128,
		.chunk_max = xpages / 128,
	};
}

static t_config config_large()
{
	size_t small_xpages;

	small_xpages = getpagesize() * 32;
	return (t_config){
		.heap_size = (size_t)-1,
		.chunk_min = small_xpages / 128,
		.chunk_max = (size_t)-1};
}

extern t_config get_config(t_config_type type)
{
	static t_config (*config[TYPES])() =
		{
			[TINY] = &config_tiny,
			[SMALL] = &config_small,
			[LARGE] = &config_large,
		};

	return config[type]();
}

extern t_config_type get_config_type(size_t size)
{
	t_config config;
	t_config_type type;

	type = 0;
	while (type < TYPES)
	{
		config = get_config(type);
		if (size < config.chunk_max)
			break;
		type++;
	}
	return type;
}