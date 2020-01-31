#include <unistd.h>
#include <string.h>

void print_string(char *str)
{
	write(1, str, strlen(str));
}