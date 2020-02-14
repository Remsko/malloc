/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:37:18 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:41:00 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "align.h"

void	*valloc(size_t size)
{
	size_t xpages;

	xpages = page_align(size);
	if (xpages < size)
		return (NULL);
	return (malloc(xpages));
}
