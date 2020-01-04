#include <errno.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

struct list
{
	int val;
	struct list *next;
};
static struct list *list_bot;
static struct list *list_top;
static long list_siz;

int list_init(long len)
{
	list_top = (struct list *)mmap(NULL, len * sizeof(struct list), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (list_top == MAP_FAILED)
		return -1;
	list_bot = list_top;
	list_siz = len;
	printf("list_init : top=%p , len=%ld \n ", list_top, len);
	return 0;
}

struct list *list_alloc1()
{
	long siz = list_top - list_bot;
	if (siz >= list_siz)
	{
		errno = ENOMEM;
		return NULL;
	}
	list_top->next = NULL;
	printf("allocated %p ( length : %ld ) \n ",
		   list_top, siz + 1);
	return list_top++;
}

struct list *list_free()
{
	return NULL;
}

struct list *list_add(struct list *l, int val)
{
	struct list *elt;
	if ((elt = list_alloc1()) == NULL)
		return NULL;
	elt->val = val;
	elt->next = l;
	return elt;
}

void list_visit(const char *label, struct list *l)
{
	printf("[%s]visit list:", label);
	while (l != NULL)
	{
		printf("%d\n", l->val);
		l = l->next;
	}
	printf("\n");
}

int main(void)
{
	struct list *l = NULL;
	pid_t pid;
	if (list_init(1000) < 0)
		exit(EXIT_FAILURE);
	if ((l = list_add(l, 42)) == NULL || (l = list_add(l, 17)) == NULL || (l = list_add(l, 13)) == NULL)
		exit(EXIT_FAILURE);
	list_visit("common", l);
	if ((pid = fork()) < 0)
		exit(EXIT_FAILURE);
	if (pid > 0)
	{ /*parent*/
		l = list_add(l, 7);
		list_visit("parent", l);
	}
	else
	{ /*child*/
		l = list_add(l, 5);
		list_visit("child", l);
	}
	exit(EXIT_SUCCESS);
}