/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:47:55 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:56:23 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <stddef.h>

void	*get_some_memory(size_t size)
{
	void *memory;

	memory = mmap(NULL, size, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (memory == MAP_FAILED)
		return (NULL);
	return (memory);
}

void	release_some_memory(void *memory, size_t size)
{
	munmap(memory, size);
}
