/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:37:02 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:40:34 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*reallocf(void *ptr, size_t size)
{
	void *p;

	p = realloc(ptr, size);
	if (p == NULL)
		free(ptr);
	return (p);
}
