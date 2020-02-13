#include "test.h"
#include <stdio.h>

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

void multiple2(void)
{
	putstr("Multiple2:");
	void *test1[130];
	for (int i = 0; i < 130; i++)
	{
		test1[i] = malloc(50);
	}

	for (int i = 0; i < 130; i++)
	{
		free(test1[i]);
	}
	putstr(" OK\n");
}

void corrupt(void)
{
	putstr("Corrupt:");
	void *ptr = malloc(50);
	free(ptr + 5);
	putstr(" OK\n");
}

#include <string.h>
#include "debug.h"
#include "chunk.h"
int test_6_copy(void)
{
	void *data[5000];

	for (size_t len = 0; len < 5000; len += 3)
	{
		char cmp[len];
		memset(cmp, 'a', len);

		for (size_t i = 1; i < 5000; i += 3)
		{
			data[i] = malloc(len);
			if (data[i] == NULL)
			{
				print_number("fail", len);
				return (0);
			}
			memset(data[i], 'a', len);

			if ((size_t)data[i] % 16 != 0)
			{
				print_number("not aligned", len);
				return (0);
			}
		}

		for (size_t i = 1; i < 5000; i += 3)
		{
			if (memcmp(cmp, data[i], len) != 0)
			{
				print_number("first cmp", len);
				return (0);
			}
		}

		for (size_t i = 1; i < 5000; i += 3)
		{
			if (len == 963 && i == 787)
				// return (0);
				if (memcmp(cmp, data[i], len) != 0)
				{
					print_number("second cmp", len);
					return (0);
				}

			//print_number("len", len);
			//print_number("i", i);
			// if (len == 963 && i == 784)
			// {
			// 	show_alloc_mem();
			// 	printf("@: 0x%lX\n", (unsigned long)((void *)data[i] - sizeof(t_chunk)));
			// }
			free(data[i]);
		}
	}
	return (0);
}

int main(void)
{
	//test_search_chunk();
	//test_search_heap();

	// test_free_null();
	// test_oversized_malloc();
	// test_zero_malloc();
	// test_zero_malloc_free();

	//print_string("before test\n");
	// test_simple(5);
	// test_simple(500);
	// test_simple(5000);
	// test_simple(50000);
	// test_simple(500000);
	// test_simple(4096 * 2);
	// test_simple(4096 * 4);
	// test_simple(4096 * 8);
	// test_simple(4096 * 16);

	//print_string("after test\n");
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

	// multiple();
	// multiple2();
	// corrupt();

	test_6_copy();
	show_alloc_mem();
	//test_coalesce();

	return 0;
}