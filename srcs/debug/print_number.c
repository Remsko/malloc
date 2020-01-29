#include "debug.h"
#include "string.h"
#include <stddef.h>

void ft_putnbr(size_t nb)
{
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		print_string((char[1]){nb + '0'});
}

void print_number(char *input, size_t nb)
{
	char str[31];

	bzero(str, 30);
	print_string(input);
	print_string(": ");
	ft_putnbr(nb);
	print_string(str);
	print_string(";\n");
}