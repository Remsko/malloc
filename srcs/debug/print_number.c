#include "debug.h"
#include "string.h"
#include <stddef.h>
#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int putnbr2(size_t n)
{
	if (n >= 10)
	{
		putnbr2(n / 10);
		ft_putchar(n % 10 + '0');
	}
	if (n < 10)
	{
		ft_putchar(n % 10 + '0');
	}
	return (n);
}

void print_number(char *input, size_t nb)
{
	print_string(input);
	print_string(": ");
	putnbr2(nb);
	print_string(";\n");
}
