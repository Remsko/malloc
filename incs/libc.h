#ifndef LIBC_H
#define LIBC_H

#include "chunk.h"
#include <stddef.h>

void *ft_memset(void *s, int c, size_t n);
void *ft_memcpy(void *dst, const void *src, size_t n);
void *ft_memmove(void *dst, const void *src, size_t n);
void ft_bzero(void *s, size_t len);

// bool rb_tree_heap_insert(t_rb_tree **root, t_rb_tree *heap, int (*cmp_f)(void *, void *));
// t_heap *rb_tree_heap_new(void *memory, size_t size);
// t_rb_tree *rb_tree_heap_search(t_rb_tree *root, t_rb_tree *heap, int (*cmp_f)(void *, void *));
// t_rb_tree *rb_tree_heap_chunk_search(t_rb_tree *root, t_chunk *chunk, int (*cmp_f)(t_chunk *, void *));

#endif