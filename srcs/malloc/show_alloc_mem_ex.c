/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:37:15 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:43:45 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "arena.h"
#include "heap.h"
#include "chunk.h"
#include "ft_printf.h"
#include <stdbool.h>

static void	show_ex(void *mem, size_t size)
{
	size_t	i;
	bool	nl;

	i = 0;
	while (i < size)
	{
		nl = (i % 10 == 0);
		ft_printf("%s%0.2X", nl ? "\n" : " ", ((unsigned char*)mem)[i]);
		i++;
	}
}

static void	show_chunk_ex(t_chunk *chunk)
{
	void	*payload;
	size_t	payload_size;

	payload = get_chunk_payload(chunk);
	payload_size = get_payload_size(chunk);
	if (!chunk_is_free(chunk))
	{
		ft_printf("0x%lX - 0x%lX :",
			(unsigned long)chunk,
			(unsigned long)get_next_chunk(chunk));
		show_ex(payload, payload_size);
		ft_printf("\n");
	}
}

static void	show_heap_ex(t_heap *heap, t_config_type type)
{
	t_chunk	*chunk;

	ft_printf("%s : 0x%lX\n", config_type_to_string(type), (unsigned long)heap);
	chunk = get_first_chunk(heap);
	while (chunk_is_on_heap(heap, chunk))
	{
		show_chunk_ex(chunk);
		chunk = get_next_chunk(chunk);
	}
}

static void	show_alloc_mem_unclocked_ex(void)
{
	t_heap			**heap;
	t_config_type	type;

	type = 0;
	while (type < TYPES)
	{
		heap = get_arena_heap_head(type);
		if (heap != NULL)
		{
			while ((*heap) != NULL)
			{
				show_heap_ex(*heap, type);
				heap = &(*heap)->next;
			}
		}
		type++;
	}
}

void		show_alloc_mem_ex(void)
{
	pthread_mutex_lock(&g_thread_mutex);
	show_alloc_mem_unclocked_ex();
	pthread_mutex_unlock(&g_thread_mutex);
}
