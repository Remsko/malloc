#include "config.h"
#include <unistd.h>
#include <assert.h>

static t_config config_tiny(void)
{
	size_t xpages;

	xpages = getpagesize() * 4;
	return (t_config){
		.heap_size = xpages,
		.chunk_min = 1,
		.chunk_max = xpages / 128,
	};
}

static t_config config_small(void)
{
	size_t xpages;

	xpages = getpagesize() * 32;
	return (t_config){
		.heap_size = xpages,
		.chunk_min = config_tiny().chunk_max,
		.chunk_max = xpages / 128,
	};
}

static t_config config_large(void)
{
	return (t_config){
		.heap_size = (size_t)-1,
		.chunk_min = config_small().chunk_max,
		.chunk_max = (size_t)-1};
}

t_config get_config(t_config_type type)
{
	static t_config (*config[TYPES])(void) =
		{
			[TINY] = &config_tiny,
			[SMALL] = &config_small,
			[LARGE] = &config_large,
		};

	return config[type]();
}

t_config_type get_config_type(size_t size)
{
	t_config config;
	t_config_type type;

	type = 0;
	while (type < TYPES)
	{
		config = get_config(type);
		if (size <= config.chunk_max)
			break;
		type++;
	}
	return type;
}

char *config_type_to_string(t_config_type type)
{
	switch (type)
	{
	case TINY:
		return "TINY";
	case SMALL:
		return "SMALL";
	case LARGE:
		return "LARGE";
	default:
		assert(1);
		return NULL;
	}
}