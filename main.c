#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./incs/malloc.h"

#define ALIGNMENT 4096
#define ALIGN(size) (size_t)(((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

typedef struct s_header
{
	size_t block_size;
	bool free;
} t_header;

#define HEADER_SIZE sizeof(t_header)

int main()
{
	printf("%d\n", 1 << 14);
	printf("%d\n", 1 << 4);
	printf("%zu\n", sizeof(t_header));
	printf("%zu\n", sizeof(t_chunk));
	printf("%zu\n", sizeof(t_chunk *));

	// char *allocation = malloc(8);
	// if (allocation == NULL)
	// {
	// 	perror("Could not malloc");
	// 	return 0;
	// }

	// for (int i = 0; i < 4096 * 32 + 1; i++)
	// {
	// 	allocation[i] = 'a';
	// }
	// write(1, allocation * 32 + 1);

	printf("1234 aligned to: %zu;\n", ALIGN(1234));
	printf("129845 aligned to: %zu;\n", ALIGN(129845));
	printf("12 aligned to: %zu;\n", ALIGN(12));
	printf("6546 aligned to: %zu;\n", ALIGN(6546));
	printf("435234 aligned to: %zu;\n", ALIGN(435234));
	printf("64323 aligned to: %zu;\n", ALIGN(64323));
	printf("12345435 aligned to: %zu;\n", ALIGN(12345435));

	return 0;
}