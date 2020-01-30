#include "test.h"

int main(void)
{
	// test_split_chunk();
	test_search_chunk();

	// test_free_null();
	// test_oversized_malloc();
	// test_zero_malloc();
	// test_zero_malloc_free();

	test_simple(5);
	test_simple(500);
	test_simple(5000);
	test_simple(50000);
	test_simple(500000);
	test_simple(4096 * 2);
	test_simple(4096 * 4);
	test_simple(4096 * 8);
	test_simple(4096 * 16);

	for (int i = 0; i < 450; i++)
	{
		test_simple(256);
	}

	// test_simple_free(5);
	// test_simple_free(500);
	// test_simple_free(5000);
	// test_simple_free(50000);
	// test_simple_free(500000);
	// test_simple_free(4096);
	// test_simple_free(4096 * 2);
	// test_simple_free(4096 * 4);
	// test_simple_free(4096 * 8);
	// test_simple_free(4096 * 16);

	// test_write_free(5);
	// test_write_free(500);
	// test_write_free(5000);
	// test_write_free(50000);
	// test_write_free(500000);

	return 0;
}