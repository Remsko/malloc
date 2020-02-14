/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:15:43 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:15:50 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIGN_H
# define ALIGN_H

# include <stddef.h>

# define MEMORY_ALIGNMENT 16UL

size_t align(size_t size, size_t alignment);
size_t page_align(size_t size);
size_t memory_align(size_t size);

#endif
