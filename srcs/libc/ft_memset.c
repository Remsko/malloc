/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:34:07 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:36:00 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

inline static void	align_word(unsigned char **pdst, unsigned char c, size_t *n)
{
	while (*n > 0 && (size_t)(*pdst) % sizeof(unsigned long) > 0)
	{
		(*pdst)[0] = c;
		*pdst += 1;
		*n -= 1;
	}
}

inline static void	block_set(unsigned long **pdst, unsigned long cccc,
		size_t blocks)
{
	while (blocks > 0)
	{
		(*pdst)[0] = cccc;
		(*pdst)[1] = cccc;
		(*pdst)[2] = cccc;
		(*pdst)[3] = cccc;
		(*pdst)[4] = cccc;
		(*pdst)[5] = cccc;
		(*pdst)[6] = cccc;
		(*pdst)[7] = cccc;
		*pdst += 8;
		blocks -= 1;
	}
}

inline static void	word_set(unsigned long **pdst, unsigned long cccc,
		size_t words)
{
	while (words > 0)
	{
		(*pdst)[0] = cccc;
		*pdst += 1;
		words -= 1;
	}
}

inline static void	byte_set(unsigned char **pdst, unsigned char c,
		size_t bytes)
{
	while (bytes > 0)
	{
		(*pdst)[0] = c;
		*pdst += 1;
		bytes -= 1;
	}
}

void				*ft_memset(void *s, int c, size_t n)
{
	void			*p;
	unsigned long	cccc;

	p = s;
	if (n >= sizeof(unsigned long))
	{
		cccc = (unsigned char)c;
		cccc |= cccc << 8;
		cccc |= cccc << 16;
		cccc |= cccc << 32;
		align_word((unsigned char **)&s, (unsigned char)c, &n);
		block_set((unsigned long **)&s, cccc, n / (8 * sizeof(unsigned long)));
		n %= (8 * sizeof(unsigned long));
		word_set((unsigned long **)&s, cccc, n / sizeof(unsigned long));
		n %= sizeof(unsigned long);
	}
	byte_set((unsigned char **)&s, (unsigned char)c, n);
	return (p);
}
