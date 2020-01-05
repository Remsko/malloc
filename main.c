#include <stdio.h>

typedef struct s_header
{
	size_t block_size;
} t_header;

#define HEADER_SIZE sizeof(t_header)

int main()
{
	printf("%d\n", 1 << 14);
	printf("%d\n", 1 << 4);
	printf("%zu\n", sizeof(t_header));
}