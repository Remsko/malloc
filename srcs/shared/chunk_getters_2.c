/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_getters_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:04:01 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 16:05:22 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "chunk.h"

size_t	get_payload_size(t_chunk *chunk)
{
	return (get_chunk_size(chunk) - sizeof(t_chunk));
}

t_chunk	*get_first_chunk(t_heap *heap)
{
	return ((t_chunk*)((void *)heap + sizeof(t_heap)));
}

t_chunk	*get_free_chunk(t_heap **head, size_t chunk_size)
{
	t_heap	*new_heap;
	size_t	new_heap_size;
	t_chunk	*chunk;

	if ((chunk = search_free_chunk(head, chunk_size)))
		return (chunk);
	new_heap_size = get_heap_size(chunk_size);
	if (new_heap_size < chunk_size)
		return (NULL);
	new_heap = arena_insert(head, new_heap_size);
	if (new_heap == NULL)
		return (NULL);
	chunk = init_chunk(new_heap);
	split_chunk(new_heap, chunk, chunk_size);
	return (chunk);
}
