#ifndef CONFIG_H
#define CONFIG_H

#include <stddef.h>

typedef enum e_config_type
{
	TINY = 0,
	SMALL = 1,
	LARGE = 2,
	TYPES = 3
} t_config_type;

typedef struct s_config
{
	size_t heap_size;
	size_t chunk_size;
} t_config;

t_config get_config(t_config_type type);
t_config_type get_config_type(size_t size);

#endif