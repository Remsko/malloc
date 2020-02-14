/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:47:26 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:52:57 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "heap.h"
#include "config.h"
#include "align.h"
#include "memory.h"
#include "malloc.h"
#include <assert.h>

t_arena		*get_arena_singletone(void)
{
	static t_arena arena = { .tiny = NULL, .small = NULL, .large = NULL};

	return (&arena);
}

t_heap		**get_arena_heap_head(t_config_type type)
{
	t_arena *arena;

	arena = get_arena_singletone();
	if (type == TINY)
		return (&arena->tiny);
	if (type == SMALL)
		return (&arena->small);
	return (&arena->large);
}

t_heap		**get_arena_heap_by_size(size_t size)
{
	t_config_type type;

	type = get_config_type(size);
	return (get_arena_heap_head(type));
}

t_heap		*arena_insert(t_heap **head, size_t size)
{
	t_heap	*new;
	void	*memory;

	memory = get_some_memory(size);
	new = insert_new_heap(head, memory, size);
	return (new);
}
