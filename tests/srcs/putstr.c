#include <unistd.h>
#include <string.h>

void putstr(char *str)
{
	write(1, str, strlen(str));
}

void printchar(char c)
{
	write(1, &c, 1);
}

size_t putnbr(size_t n)
{
	if (n >= 10)
	{
		putnbr(n / 10);
		printchar(n % 10 + '0');
	}
	if (n < 10)
	{
		printchar(n % 10 + '0');
	}
	return (n);
}