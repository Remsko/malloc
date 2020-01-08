#include "test.h"

void test_oversized_malloc()
{
	putstr("Oversized malloc: ");
	size_t oversized = (size_t)-1;
	if (malloc(oversized))
		return putstr("FAIL\n");
	putstr("OK\n");
}