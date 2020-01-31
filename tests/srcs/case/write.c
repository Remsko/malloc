#include "test.h"
#include <string.h>

void test_write(size_t size)
{
	char cpy[size];
	void *ptr;

	putstr("Write: ");
	ptr = malloc(size);
	if (!ptr)
		return putstr("FAIL\n");
	cpy[size - 1] = '\0';
	strcpy(ptr, cpy);
	if (strcmp(ptr, cpy))
		return putstr("FAIL\n");
	putstr("OK\n");
}

void test_write_free(size_t size)
{
	char cpy[size];
	void *ptr;

	putstr("Write + Free: ");
	ptr = malloc(size);
	if (!ptr)
		return putstr("FAIL\n");
	cpy[size - 1] = '\0';
	strcpy(ptr, cpy);
	if (strcmp(ptr, cpy))
		return putstr("FAIL\n");
	free(ptr);
	putstr("OK\n");
}