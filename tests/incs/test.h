#ifndef TEST_H
#define TEST_H

#include <stddef.h>
#include "malloc.h"

void putstr(char *str);

void test_free_null();
void test_oversized_malloc();
void test_write(size_t size);
void test_write_free(size_t size);
void test_simple(size_t size);
void test_simple_free(size_t size);
void test_zero_malloc();
void test_zero_malloc_free();

#endif