/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:06:33 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 16:08:19 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chunk.h"

static void		update_next_chunk(t_heap *heap, t_chunk *chunk)
{
	t_chunk *next;

	next = get_next_chunk(chunk);
	if (chunk_is_on_heap(heap, next))
		next->backward = get_chunk_size(chunk);
}

t_chunk			*split_chunk(t_heap *heap, t_chunk *chunk, size_t size)
{
	t_chunk	*split;
	size_t	rest;

	rest = get_chunk_size(chunk) - size;
	if (sizeof(t_chunk) + 1 <= rest)
	{
		new_chunk((void *)chunk, size);
		split = new_chunk((void *)chunk + size, rest);
		split->backward = size;
		update_next_chunk(heap, split);
	}
	return (chunk);
}

static t_chunk	*merge_chunk(t_chunk *start, t_chunk *end)
{
	start->forward += get_chunk_size(end);
	return (start);
}

t_chunk			*coalesce_chunk(t_heap *heap, t_chunk *chunk)
{
	t_chunk	*next;
	t_chunk	*prev;
	bool	coalescion;

	coalescion = false;
	next = get_next_chunk(chunk);
	if (chunk_is_on_heap(heap, next) && chunk_is_free(next) && next != chunk)
	{
		coalescion = true;
		merge_chunk(chunk, next);
	}
	prev = get_previous_chunk(chunk);
	if (chunk_is_on_heap(heap, prev) && chunk_is_free(prev) && prev != chunk)
	{
		coalescion = true;
		chunk = merge_chunk(prev, chunk);
	}
	if (coalescion)
		update_next_chunk(heap, chunk);
	return (chunk);
}
