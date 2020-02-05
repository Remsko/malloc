#include "heap.h"
#include "chunk.h"
#include "debug.h"

extern void print_heap(t_heap *heap)
{
    t_chunk *chunk;

    print_string("heap(");
    ft_putnbr(heap->size);
    print_string("): ");
    ft_putnbr((size_t)heap);
    print_string("|");
    ft_putnbr((size_t)((size_t)heap + heap->size));
    print_string(";");
    chunk = get_first_chunk(heap);
    print_string("[");
    ft_putnbr(is_chunk_free(chunk));
    print_string("]");
    ft_putnbr((size_t)chunk);
    print_string("(");
    ft_putnbr(chunk->backward);
    print_string("-");
    ft_putnbr(get_chunk_size(chunk));
    print_string(")");
    chunk = get_next_chunk(chunk);
    while (chunk_is_on_heap(heap, chunk))
    {
        print_string("->");
        print_string("[");
        ft_putnbr(is_chunk_free(chunk));
        print_string("]");
        ft_putnbr((size_t)chunk);
        print_string("(");
        ft_putnbr(chunk->backward);
        print_string("-");
        ft_putnbr(get_chunk_size(chunk));
        print_string(")");
        chunk = get_next_chunk(chunk);
    }
    print_string("-END-");
    ft_putnbr((size_t)chunk);
    print_string("\n");
}