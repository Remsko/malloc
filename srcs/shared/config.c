#include "config.h"
#include <unistd.h>

static t_config config_tiny()
{
	size_t xpages;

	xpages = getpagesize() * 4;
	return (t_config){
		.heap_size = xpages,
		.chunk_size = xpages / 128,
	};
}

static t_config config_small()
{
	size_t xpages;

	xpages = getpagesize() * 32;
	return (t_config){
		.heap_size = xpages,
		.chunk_size = xpages / 128,
	};
}

static t_config config_large()
{
	return (t_config){(size_t)-1, (size_t)-1};
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
		if (size < config.chunk_size)
			break;
		type++;
	}
	return type;
}