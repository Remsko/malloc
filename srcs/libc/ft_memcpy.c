/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:33:55 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:34:53 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

inline static void	align_copy_fwd(unsigned char **pdst,
		const unsigned char **psrc, size_t *n)
{
	while (*n > 0 && (size_t)(*pdst) % sizeof(unsigned long) > 0)
	{
		(*pdst)[0] = (*psrc)[0];
		*pdst += 1;
		*psrc += 1;
		*n -= 1;
	}
}

inline static void	block_copy_fwd(unsigned long **pdst,
		const unsigned long **psrc, size_t blocks)
{
	while (blocks > 0)
	{
		(*pdst)[0] = (*psrc)[0];
		(*pdst)[1] = (*psrc)[1];
		(*pdst)[2] = (*psrc)[2];
		(*pdst)[3] = (*psrc)[3];
		(*pdst)[4] = (*psrc)[4];
		(*pdst)[5] = (*psrc)[5];
		(*pdst)[6] = (*psrc)[6];
		(*pdst)[7] = (*psrc)[7];
		*pdst += 8;
		*psrc += 8;
		blocks -= 1;
	}
}

inline static void	word_copy_fwd(unsigned long **pdst,
		const unsigned long **psrc, size_t words)
{
	while (words > 0)
	{
		(*pdst)[0] = (*psrc)[0];
		*pdst += 1;
		*psrc += 1;
		words -= 1;
	}
}

inline static void	byte_copy_fwd(unsigned char **pdst,
		const unsigned char **psrc, size_t bytes)
{
	while (bytes > 0)
	{
		(*pdst)[0] = (*psrc)[0];
		*pdst += 1;
		*psrc += 1;
		bytes -= 1;
	}
}

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	void *p;

	p = dst;
	if (n >= sizeof(unsigned long))
	{
		align_copy_fwd((unsigned char **)&dst, (const unsigned char **)&src,
				&n);
		block_copy_fwd((unsigned long **)&dst, (const unsigned long **)&src,
				n / (8 * sizeof(unsigned long)));
		n %= (8 * sizeof(unsigned long));
		word_copy_fwd((unsigned long **)&dst, (const unsigned long **)&src,
				n / sizeof(unsigned long));
		n %= sizeof(unsigned long);
	}
	byte_copy_fwd((unsigned char **)&dst, (const unsigned char **)&src, n);
	return (p);
}
