#include <unistd.h>

size_t align(size_t size, size_t alignment)
{
	return ((size) + (alignment - 1)) & ~(alignment - 1);
}

size_t page_align(size_t size)
{
	return align(size, (size_t)getpagesize());
}

size_t memory_align(size_t size)
{
	return align(size, 16);
}