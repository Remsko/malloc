/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:36:37 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:37:58 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libc.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	total = count * size;
	if (total / count != size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr)
		ft_bzero(ptr, count * size);
	return (ptr);
}
