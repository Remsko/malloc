#include "test.h"

void test_zero_malloc()
{
	putstr("Malloc(0): ");
	malloc(0);
	putstr("OK\n");
}

void test_zero_malloc_free()
{
	putstr("Malloc(0) + Free: ");
	free(malloc(0));
	putstr("OK\n");
}