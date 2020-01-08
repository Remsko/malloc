#include <unistd.h>

inline size_t align(size_t size, size_t alignment)
{
	return ((size) + (alignment - 1)) & ~(alignment - 1);
}

inline size_t page_align(size_t size)
{
	return align(size, (size_t)getpagesize());
}

inline size_t memory_align(size_t size)
{
	return align(size, 16);
}