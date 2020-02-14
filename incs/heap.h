/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:29:07 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:30:51 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

# include "config.h"
# include <pthread.h>

typedef struct	s_heap
{
	struct s_heap	*next;
	size_t			size;
}				t_heap;

t_heap			*get_heap(void *alloc);
size_t			get_heap_size(size_t chunk_size);
t_heap			*new_heap(void *alloc, size_t alloc_size);
t_heap			*insert_heap(t_heap **head, t_heap *new);
t_heap			*insert_new_heap(t_heap **head, void *alloc, size_t alloc_size);

void			delete_heap(t_heap **head, t_heap *delete);
void			release_heap_maybe(t_heap **head, t_heap *heap);

#endif
