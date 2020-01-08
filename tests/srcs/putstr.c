#include <unistd.h>
#include <string.h>

void putstr(char *str)
{
	write(1, str, strlen(str));
}