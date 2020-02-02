#include "test.h"

void multiple(void)
{
	putstr("Multiple:");
	void *test1[250];
	void *test2[250];
	void *test3[250];
	for (int i = 0; i < 250; i++)
	{
		test1[i] = malloc(50);
		test2[i] = malloc(500);
		test3[i] = malloc(5000);
	}

	for (int i = 0; i < 250; i++)
	{
		free(test1[i]);
		free(test2[i]);
		free(test3[i]);
	}
	putstr(" OK\n");
}

int main(void)
{
	test_search_chunk();
	test_search_heap();

	test_free_null();
	test_oversized_malloc();
	test_zero_malloc();
	test_zero_malloc_free();

	test_simple(5);
	test_simple(500);
	test_simple(5000);
	test_simple(50000);
	test_simple(500000);
	test_simple(4096 * 2);
	test_simple(4096 * 4);
	test_simple(4096 * 8);
	test_simple(4096 * 16);

	test_simple_free(500);
	test_simple_free(5000);
	test_simple_free(50000);
	test_simple_free(500000);
	test_simple_free(4096);
	test_simple_free(4096 * 2);
	test_simple_free(4096 * 4);
	test_simple_free(4096 * 8);
	test_simple_free(4096 * 16);

	test_write_free(5);
	test_write_free(500);
	test_write_free(5000);
	test_write_free(50000);
	test_write_free(500000);

	multiple();

	return 0;
}