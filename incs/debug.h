#ifndef DEBUG_H
#define DEBUG_H

#include "heap.h"
#include <stddef.h>

void print_string(char *str);
void print_number(char *input, size_t nb);
void print_heap(t_heap *heap);
int putnbr2(size_t n);

#endif