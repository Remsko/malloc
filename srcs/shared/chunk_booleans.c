/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_booleans.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:00:35 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 16:01:27 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include "chunk.h"

bool	chunk_is_available(t_chunk *chunk, size_t s)
{
	return (chunk_is_free(chunk) && s <= get_chunk_size(chunk));
}

bool	chunk_is_on_heap(t_heap *heap, t_chunk *chunk)
{
	void *start;
	void *end;

	start = (void *)heap;
	end = (void *)heap + heap->size;
	return ((void *)chunk > start && (void *)chunk < end);
}

bool	chunk_is_corrupt(t_heap *heap, t_chunk *search)
{
	t_chunk *compare;

	if (heap == NULL)
		return (true);
	compare = get_first_chunk(heap);
	while (chunk_is_on_heap(heap, compare))
	{
		if (compare == search)
			return (false);
		compare = get_next_chunk(compare);
	}
	return (true);
}

bool	chunk_is_free(t_chunk *chunk)
{
	return ((bool)(chunk->forward & FLAG_FREE));
}
