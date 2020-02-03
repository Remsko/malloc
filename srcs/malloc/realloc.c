#include "malloc.h"
#include <string.h>
#include "debug.h"

void *realloc(void *ptr, size_t size)
{
	size_t new = size;
	size_t old = size; //chunk->forward;
	(void)new;
	(void)old;
	(void)ptr;
	void *re = malloc(size);
	if (re)
	{
		; //memcpy(re, ptr, (new < old) ? new : old);
	}
	return re;
}