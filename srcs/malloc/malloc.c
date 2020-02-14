#include "align.h"
#include "chunk.h"
#include "malloc.h"
#include "arena.h"
#include "ft_printf.h"

pthread_mutex_t g_thread_mutex = PTHREAD_MUTEX_INITIALIZER;

char malloc_debug(void)
{
	extern char **environ;
	char flags;
	int i;

	flags = 0;
	if (environ != NULL)
	{
		i = 0;
		while (environ[i] != NULL)
		{
			if (strcmp(environ[i],"MALLOC_SIZE=1") == 0)
				flags |= 1;
			if (strcmp(environ[i],"MALLOC_ORIGINAL_SIZE=1") == 0)
				flags |= 1 << 1;
			i++;
		}
	}
	return flags;
}

void *malloc_unlocked(size_t size)
{
	t_heap **head;
	t_chunk *chunk;
	size_t chunk_size;
	char options;

	options = malloc_debug();
	if (options & (1 << 1))
		ft_printf("Malloc original size: %zu\n", size);
	if (size == 0)
		size = 1;
	chunk_size = memory_align(size + sizeof(t_chunk));
	if (chunk_size < size)
		return NULL;
	if (options & 1)
		ft_printf("Malloc size: %zu\n", chunk_size);
	head = get_arena_heap_by_size(chunk_size);
	chunk = get_free_chunk(head, chunk_size);
	if (chunk == NULL)
		return NULL;
	set_chunk_used(chunk);
	return get_chunk_payload(chunk);
}

void *malloc(size_t size)
{
	void *payload;

	pthread_mutex_lock(&g_thread_mutex);
	payload = malloc_unlocked(size);
	pthread_mutex_unlock(&g_thread_mutex);
	return payload;
}