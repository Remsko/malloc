#include "chunk.h"
#include "malloc.h"
#include "arena.h"
#include "ft_printf.h"
#include "libc.h"

char free_debug(void)
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
			if (ft_strcmp(environ[i],"DEBUG_FREE=1") == 0)
				flags |= 1;
			i++;
		}
	}
	return flags;
}

void free_unlocked(void *ptr)
{
	t_heap **head;
	t_heap *heap;
	t_chunk *chunk;
	char options;

	options = free_debug();
	if (ptr == NULL)
		return;
	chunk = get_chunk_from_payload(ptr);
	if (!search_heap_in_heaps(chunk, &head, &heap))
		return;
	if (chunk_is_corrupt(heap, chunk))
	{
		if (options & 1)
			ft_printf("Pointer freed was not allocated: %p\n", ptr);
		return;
	}
	set_chunk_free(chunk);
	chunk = coalesce_chunk(heap, chunk);
	release_heap_maybe(head, heap);
}

void free(void *ptr)
{
	pthread_mutex_lock(&g_thread_mutex);
	free_unlocked(ptr);
	pthread_mutex_unlock(&g_thread_mutex);
}
