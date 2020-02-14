/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:47:38 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 16:00:17 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chunk.h"

t_chunk	*new_chunk(void *start, size_t size)
{
	t_chunk *chunk;

	chunk = (t_chunk*)start;
	chunk->forward = size;
	set_chunk_free(chunk);
	return (chunk);
}

t_chunk	*init_chunk(t_heap *heap)
{
	t_chunk *chunk;

	chunk = get_first_chunk(heap);
	chunk->forward = heap->size - sizeof(t_heap);
	chunk->backward = 0;
	return (chunk);
}
