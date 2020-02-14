/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:37:11 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:46:15 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include "chunk.h"
#include "config.h"
#include "arena.h"
#include "malloc.h"
#include "ft_printf.h"

static void		show_chunk(t_chunk *chunk)
{
	if (!chunk_is_free(chunk))
		ft_printf("0x%lX - 0x%lX : %zu octets\n", (unsigned long)chunk,
			(unsigned long)get_next_chunk(chunk), get_chunk_size(chunk));
}

static void		show_heap(t_heap *heap, t_config_type type)
{
	t_chunk *chunk;

	ft_printf("%s : 0x%lX\n", config_type_to_string(type), (unsigned long)heap);
	chunk = get_first_chunk(heap);
	while (chunk_is_on_heap(heap, chunk))
	{
		show_chunk(chunk);
		chunk = get_next_chunk(chunk);
	}
}

static size_t	show_heap_and_count(t_config_type type)
{
	t_heap	**heap;
	size_t	heap_type_total;

	heap_type_total = 0;
	heap = get_arena_heap_head(type);
	if (heap != NULL)
	{
		while ((*heap) != NULL)
		{
			show_heap(*heap, type);
			heap_type_total += (*heap)->size;
			heap = &(*heap)->next;
		}
	}
	return (heap_type_total);
}

static void		show_alloc_mem_unclocked(void)
{
	size_t			total;
	t_config_type	type;

	type = 0;
	total = 0;
	while (type < TYPES)
	{
		total += show_heap_and_count(type);
		type++;
	}
	ft_printf("Total : %zu octets\n", total);
}

void			show_alloc_mem(void)
{
	pthread_mutex_lock(&g_thread_mutex);
	show_alloc_mem_unclocked();
	pthread_mutex_unlock(&g_thread_mutex);
}
