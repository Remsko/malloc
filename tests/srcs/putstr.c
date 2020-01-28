#include <unistd.h>
#include <string.h>

void putstr(char *str)
{
	write(1, str, strlen(str));
}

void putnbr(size_t size)
{
	if (size > 9)
	{
		putnbr(size / 10);
		putnbr(size % 10);
	}
	else
	{
		write(1, (char[1]){size + '0'}, 1);
	}
}