#include "test.h"

void test_free_null()
{
	putstr("Free null: ");
	free(NULL);
	putstr("OK\n");
}