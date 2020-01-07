#include "config.h"
#include <unistd.h>

t_config *config()
{
	t_config config[2];

	config[TINY] =
		(t_config){
			.heap_size = getpagesize() * 4,
			.chunk_size = 128,
		};
	config[SMALL] =
		(t_config){
			.heap_size = getpagesize() * 32,
			.chunk_size = 1024,
		};
	return config;
}