#include "malloc.h"

int main(void)
{
	void *ptr = malloc(10);
	void *ptr1 = malloc(10);
	void *ptr2 = malloc(10);
	void *ptr3 = malloc(10);
	void *ptr4 = malloc(10);
	void *ptr5 = malloc(10);
	void *ptr6 = malloc(10);
	void *ptr7 = malloc(10);
	void *ptr8 = malloc(10);
	void *ptr9 = malloc(10);
	free(ptr);
	free(ptr1);
	free(ptr2);
	free(ptr3);
	free(ptr4);
	free(ptr5);
	free(ptr6);
	free(ptr7);
	free(ptr8);
	free(ptr9);

	return 0;
}