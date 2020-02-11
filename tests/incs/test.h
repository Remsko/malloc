#ifndef TEST_H
#define TEST_H

#include <stddef.h>
#include "malloc.h"

void putstr(char *str);
void putnbr(size_t size);

void test_free_null(void);
void test_oversized_malloc(void);
void test_write(size_t size);
void test_write_free(size_t size);
void test_simple(size_t size);
void test_simple_free(size_t size);
void test_zero_malloc(void);
void test_zero_malloc_free(void);
void test_split_chunk(void);
void test_search_chunk(void);
void test_search_heap(void);
void test_coalesce(void);

#endif