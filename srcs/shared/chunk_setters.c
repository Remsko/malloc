/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:05:42 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 16:06:02 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chunk.h"

void	set_chunk_free(t_chunk *chunk)
{
	chunk->forward |= FLAG_FREE;
}

void	set_chunk_used(t_chunk *chunk)
{
	chunk->forward &= ~FLAG_FREE;
}
