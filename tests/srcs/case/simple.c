#include "test.h"
#include <string.h>

void test_simple(size_t size)
{
	void *ptr;

	putstr("Simple: ");
	ptr = malloc(size);
	if (!ptr)
		return putstr("FAIL\n");
	*(char *)ptr = 'a';
	putstr("OK\n");
}

void test_simple_free(size_t size)
{
	void *ptr;

	putstr("Simple + Free: ");
	ptr = malloc(size);
	if (!ptr)
		return putstr("FAIL\n");
	*(char *)ptr = 'a';
	free(ptr);
	putstr("OK\n");
}