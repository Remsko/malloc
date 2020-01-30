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
	print_string(input);
	print_string(": ");
	ft_putnbr(nb);
	print_string(";\n");
}