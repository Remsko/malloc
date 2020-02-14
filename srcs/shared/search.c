/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:47:59 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 16:38:54 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include "chunk.h"
#include "arena.h"
#include "malloc.h"

t_chunk	*search_free_chunk(t_heap **head, size_t size)
{
	t_chunk	*chunk;

	if (head != NULL)
	{
		while ((*head) != NULL)
		{
			chunk = get_first_chunk(*head);
			while (chunk_is_on_heap(*head, chunk))
			{
				if (chunk_is_available(chunk, size))
				{
					split_chunk(*head, chunk, size);
					return (chunk);
				}
				chunk = get_next_chunk(chunk);
			}
			head = &(*head)->next;
		}
	}
	return (NULL);
}

bool	search_heap_in_heaps(t_chunk *chunk, t_heap ***head_fnd,
			t_heap **heap_fnd)
{
	t_heap			**head;
	t_heap			*h;
	t_config_type	type;

	type = 0;
	while (type < TYPES)
	{
		head = get_arena_heap_head(type);
		h = *head;
		while (h != NULL)
		{
			if (chunk_is_on_heap(h, chunk))
			{
				*head_fnd = head;
				*heap_fnd = h;
				return (true);
			}
			h = h->next;
		}
		type++;
	}
	return (false);
}
