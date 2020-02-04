#include "malloc.h"
#include "align.h"

void *valloc(size_t size)
{
	size_t xpages;

	xpages = page_align(size);
	if (xpages < size)
		return NULL;
	void *ptr = malloc(xpages);
	print_number("v", (size_t)ptr);
	return ptr;
}