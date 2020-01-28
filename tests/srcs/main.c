#include "test.h"

int main(void)
{
	test_split_chunk();

	test_free_null();
	test_oversized_malloc();
	test_zero_malloc();
	test_zero_malloc_free();

	test_simple(5);
	test_simple(500);
	test_simple(5000);
	test_simple(50000);
	test_simple(500000);

	for (int i = 0; i < 100; i++)
	{
		test_write(5);
		test_write(500);
		test_write(5000);
		test_write(50000);
		test_write(500000);
	}

	test_simple_free(5);
	test_simple_free(500);
	test_simple_free(5000);
	test_simple_free(50000);
	test_simple_free(500000);

	test_write_free(5);
	test_write_free(500);
	test_write_free(5000);
	test_write_free(50000);
	test_write_free(500000);

	return 0;
}