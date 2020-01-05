#include "malloc.h"
#include <unistd.h>
#include <string.h>

int main(void)
{
	void *ptr = malloc(10);
	strcpy(ptr, "delicieux\n");
	write(1, ptr, 10);

	void *ptr1 = malloc(1234);
	void *ptr2 = malloc(112);
	void *ptr3 = malloc(11235);
	void *ptr4 = malloc(23);
	void *ptr5 = malloc(54);
	void *ptr6 = malloc(1345);
	void *ptr7 = malloc(7645);
	void *ptr8 = malloc(1456);
	void *ptr9 = malloc(354);
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

	write(1, "TEST DONE\n", 10);
	return 0;
}