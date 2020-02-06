#ifndef LIBC_H
#define LIBC_H

#include <stddef.h>

void *ft_memset(void *s, int c, size_t n);
void *ft_memcpy(void *dst, const void *src, size_t n);
void *ft_memmove(void *dst, const void *src, size_t n);
void ft_bzero(void *s, size_t len);

#endif