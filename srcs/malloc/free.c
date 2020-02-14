/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:36:45 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:38:39 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chunk.h"
#include "malloc.h"
#include "arena.h"
#include "ft_printf.h"
#include "libc.h"

void	free_unlocked(void *ptr)
{
	t_heap	**head;
	t_heap	*heap;
	t_chunk	*chunk;

	if (ptr == NULL)
		return ;
	chunk = get_chunk_from_payload(ptr);
	if (!search_heap_in_heaps(chunk, &head, &heap))
		return ;
	if (chunk_is_corrupt(heap, chunk))
		return ;
	set_chunk_free(chunk);
	chunk = coalesce_chunk(heap, chunk);
	release_heap_maybe(head, heap);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_thread_mutex);
	free_unlocked(ptr);
	pthread_mutex_unlock(&g_thread_mutex);
}
