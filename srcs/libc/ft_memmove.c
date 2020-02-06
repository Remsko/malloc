#include "libc.h"

inline static void align_copy_bwd(unsigned char **pdst,
		const unsigned char **psrc, size_t *n)
{
	while (*n > 0 && (size_t)(*pdst) % sizeof(unsigned long) > 0)
	{
		*pdst -= 1;
		*psrc -= 1;
		(*pdst)[0] = (*psrc)[0];
		*n -= 1;
	}
}

inline static void block_copy_bwd(unsigned long **pdst,
		const unsigned long **psrc, size_t blocks)
{
	while (blocks > 0)
	{
		*pdst -= 8;
		*psrc -= 8;
		(*pdst)[7] = (*psrc)[7];
		(*pdst)[6] = (*psrc)[6];
		(*pdst)[5] = (*psrc)[5];
		(*pdst)[4] = (*psrc)[4];
		(*pdst)[3] = (*psrc)[3];
		(*pdst)[2] = (*psrc)[2];
		(*pdst)[1] = (*psrc)[1];
		(*pdst)[0] = (*psrc)[0];
		blocks -= 1;
	}
}

inline static void word_copy_bwd(unsigned long **pdst,
		const unsigned long **psrc, size_t words)
{
	while (words > 0)
	{
		*pdst -= 1;
		*psrc -= 1;
		(*pdst)[0] = (*psrc)[0];
		words -= 1;
	}
}

inline static void byte_copy_bwd(unsigned char **pdst,
		const unsigned char **psrc, size_t bytes)
{
	while (bytes > 0)
	{
		*pdst -= 1;
		*psrc -= 1;
		(*pdst)[0] = (*psrc)[0];
		bytes -= 1;
	}
}

void *ft_memmove(void *dst, const void *src, size_t n)
{
	void *p;

	p = dst;
	if ((unsigned long)dst - (const unsigned long)src >= n)
		ft_memcpy(dst, src, n);
	else
	{
		dst += n;
		src += n;
		if (n >= sizeof(unsigned long))
		{
			align_copy_bwd((unsigned char **)&dst, (const unsigned char **)&src,
					&n);
			block_copy_bwd((unsigned long **)&dst, (const unsigned long **)&src,
					n / (8 * sizeof(unsigned long)));
			n %= (8 * sizeof(unsigned long));
			word_copy_bwd((unsigned long **)&dst, (const unsigned long **)&src,
					n / sizeof(unsigned long));
			n %= sizeof(unsigned long);
		}
		byte_copy_bwd((unsigned char **)&dst, (const unsigned char **)&src, n);
	}
	return (p);
}
