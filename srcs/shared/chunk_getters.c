/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:03:52 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 16:05:09 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chunk.h"
#include "align.h"

size_t	get_chunk_size(t_chunk *chunk)
{
	return (chunk->forward & ~(MEMORY_ALIGNMENT - 1));
}

t_chunk	*get_chunk_from_payload(void *payload)
{
	return ((t_chunk*)(payload - sizeof(t_chunk)));
}

t_chunk	*get_next_chunk(t_chunk *chunk)
{
	return ((t_chunk*)((void *)chunk + get_chunk_size(chunk)));
}

t_chunk	*get_previous_chunk(t_chunk *chunk)
{
	return ((t_chunk*)((void *)chunk - chunk->backward));
}

void	*get_chunk_payload(t_chunk *chunk)
{
	return ((void *)chunk + sizeof(t_chunk));
}
