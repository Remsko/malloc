#include "heap.h"
#include "chunk.h"
#include "arena.h"
#include "config.h"
#include "malloc.h"
#include "debug.h"

void show_heap(t_heap *heap, t_config_type type);

// 0 0 1 => 0 1
void case_1(void)
{
    t_heap *heap;
    t_chunk *chunk1;
    t_chunk *chunk2;
    t_chunk *chunk3;

    print_string("\nCOALESCE CASE 1:\n");
    heap = arena_unshift(1, get_heap_size(1));
    chunk1 = get_first_chunk(heap);
    chunk1->forward = heap->size - sizeof(t_heap);
    chunk1->backward = 0;
    split_chunk(heap, chunk1, 1, 512);
    chunk2 = get_next_chunk(chunk1);
    split_chunk(heap, chunk2, 1, 512);
    chunk3 = get_next_chunk(chunk2);

    set_chunk_used(chunk3);

    //show_heap(heap, 1);
    coalesce_chunk(heap, chunk2);
    //show_heap(heap, 1);

    if (get_chunk_size(chunk1) != 512 + 512)
    {
        print_string("\nNO\n");
        return;
    }
    if (get_chunk_size(get_next_chunk(chunk1)) != get_heap_size(1) - sizeof(t_heap) - 512 - 512)
    {
        print_string("\nNO\n");
        return;
    }
    if (chunk_is_on_heap(heap, get_next_chunk(get_next_chunk(chunk1))))
    {
        print_string("\nNO\n");
        return;
    }
    print_string("\nOK\n");
}

// 0 0 0 => 0
void case_2(void)
{
    t_heap *heap;
    t_chunk *chunk1;
    t_chunk *chunk2;
    t_chunk *chunk3;

    heap = arena_unshift(1, get_heap_size(1));
    chunk1 = get_first_chunk(heap);
    chunk1->forward = heap->size - sizeof(t_heap);
    split_chunk(heap, chunk1, 1, 512);
    chunk2 = get_next_chunk(chunk1);
    split_chunk(heap, chunk2, 1, 512);
    chunk3 = get_next_chunk(chunk2);

    // set_chunk_used(chunk3);

    // show_heap(heap, 1);
    coalesce_chunk(heap, chunk2);
    // show_heap(heap, 1);

    if (get_chunk_size(chunk1) != get_heap_size(1) - sizeof(t_heap))
    {
        print_string("\nNO\n");
        return;
    }
    if (chunk_is_on_heap(heap, get_next_chunk(chunk1)))
    {
        print_string("\nNO\n");
        return;
    }
    print_string("\nOK\n");
}

// 1 0 0 => 1 0
void case_3(void)
{
    t_heap *heap;
    t_chunk *chunk1;
    t_chunk *chunk2;
    t_chunk *chunk3;

    heap = arena_unshift(1, get_heap_size(1));
    chunk1 = get_first_chunk(heap);
    chunk1->forward = heap->size - sizeof(t_heap);
    split_chunk(heap, chunk1, 1, 512);
    chunk2 = get_next_chunk(chunk1);
    split_chunk(heap, chunk2, 1, 512);
    chunk3 = get_next_chunk(chunk2);

    set_chunk_used(chunk1);

    // show_heap(heap, 1);
    coalesce_chunk(heap, chunk2);
    // show_heap(heap, 1);

    if (get_chunk_size(chunk1) != 512)
    {
        print_string("\nNO\n");
        return;
    }
    if (get_chunk_size(chunk2) != get_heap_size(1) - sizeof(t_heap) - 512)
    {
        print_string("\nNO\n");
        return;
    }
    if (chunk_is_on_heap(heap, get_next_chunk(chunk2)))
    {
        print_string("\nNO\n");
        return;
    }
    print_string("\nOK\n");
}

// 1 0 1
void case_4(void)
{
    t_heap *heap;
    t_chunk *chunk1;
    t_chunk *chunk2;
    t_chunk *chunk3;

    heap = arena_unshift(1, get_heap_size(1));
    chunk1 = get_first_chunk(heap);
    chunk1->forward = heap->size - sizeof(t_heap);
    split_chunk(heap, chunk1, 1, 512);
    chunk2 = get_next_chunk(chunk1);
    split_chunk(heap, chunk2, 1, 512);
    chunk3 = get_next_chunk(chunk2);

    set_chunk_used(chunk1);
    set_chunk_used(chunk3);

    // show_heap(heap, 1);
    coalesce_chunk(heap, chunk2);
    // show_heap(heap, 1);

    if (get_chunk_size(chunk1) != 512)
    {
        print_string("\nNO\n");
        return;
    }
    if (get_chunk_size(chunk2) != 512)
    {
        print_string("\nNO\n");
        return;
    }
    if (get_chunk_size(chunk3) != get_heap_size(1) - sizeof(t_heap) - 512 - 512)
    {
        print_string("\nNO\n");
        return;
    }
    print_string("\nOK\n");
}

// 0 0] => 0]
void case_5(void)
{
    t_heap *heap;
    t_chunk *chunk1;
    t_chunk *chunk2;
    t_chunk *chunk3;
    t_chunk *chunk4;

    heap = arena_unshift(1, get_heap_size(1));
    chunk1 = get_first_chunk(heap);
    chunk1->forward = heap->size - sizeof(t_heap);
    split_chunk(heap, chunk1, 1, 512);
    chunk2 = get_next_chunk(chunk1);
    split_chunk(heap, chunk2, 1, 512);
    chunk3 = get_next_chunk(chunk2);
    split_chunk(heap, chunk3, 1, 512);
    chunk4 = get_next_chunk(chunk3);

    set_chunk_used(chunk1);
    set_chunk_used(chunk2);

    // show_heap(heap, 1);
    coalesce_chunk(heap, chunk4);
    // show_heap(heap, 1);

    if (get_chunk_size(chunk3) != get_heap_size(1) - sizeof(t_heap) - 512 - 512)
    {
        print_string("\nNO\n");
        return;
    }
    if (chunk_is_on_heap(heap, get_next_chunk(chunk3)))
    {
        print_string("\nNO\n");
        return;
    }
    print_string("\nOK\n");
}

// 1 0]
void case_6(void)
{
    t_heap *heap;
    t_chunk *chunk1;
    t_chunk *chunk2;
    t_chunk *chunk3;
    t_chunk *chunk4;

    heap = arena_unshift(1, get_heap_size(1));
    chunk1 = get_first_chunk(heap);
    chunk1->forward = heap->size - sizeof(t_heap);
    split_chunk(heap, chunk1, 1, 512);
    chunk2 = get_next_chunk(chunk1);
    split_chunk(heap, chunk2, 1, 512);
    chunk3 = get_next_chunk(chunk2);
    split_chunk(heap, chunk3, 1, 512);
    chunk4 = get_next_chunk(chunk3);

    set_chunk_used(chunk1);
    set_chunk_used(chunk2);
    set_chunk_used(chunk3);

    // show_heap(heap, 1);
    coalesce_chunk(heap, chunk4);
    // show_heap(heap, 1);

    if (get_chunk_size(chunk3) != 512)
    {
        print_string("\nNO\n");
        return;
    }
    if (get_chunk_size(chunk4) != get_heap_size(1) - sizeof(t_heap) - 512 - 512 - 512)
    {
        print_string("\nNO\n");
        return;
    }
    print_string("\nOK\n");
}

// [0 0
void case_7(void)
{
    t_heap *heap;
    t_chunk *chunk1;
    t_chunk *chunk2;
    t_chunk *chunk3;
    t_chunk *chunk4;

    heap = arena_unshift(1, get_heap_size(1));
    chunk1 = get_first_chunk(heap);
    chunk1->forward = heap->size - sizeof(t_heap);
    split_chunk(heap, chunk1, 1, 512);
    chunk2 = get_next_chunk(chunk1);
    split_chunk(heap, chunk2, 1, 512);
    chunk3 = get_next_chunk(chunk2);
    split_chunk(heap, chunk3, 1, 512);
    chunk4 = get_next_chunk(chunk3);

    set_chunk_used(chunk3);
    set_chunk_used(chunk4);
    //set_chunk_used(chunk3);

    // show_heap(heap, 1);
    coalesce_chunk(heap, chunk1);
    // show_heap(heap, 1);

    if (get_chunk_size(chunk1) != 512 + 512)
    {
        print_string("\nNO\n");
        return;
    }
    print_string("\nOK\n");
}

// [0 1
void case_8(void)
{
    t_heap *heap;
    t_chunk *chunk1;
    t_chunk *chunk2;
    t_chunk *chunk3;
    t_chunk *chunk4;

    heap = arena_unshift(1, get_heap_size(1));
    chunk1 = get_first_chunk(heap);
    chunk1->forward = heap->size - sizeof(t_heap);
    split_chunk(heap, chunk1, 1, 512);
    chunk2 = get_next_chunk(chunk1);
    split_chunk(heap, chunk2, 1, 512);
    chunk3 = get_next_chunk(chunk2);
    split_chunk(heap, chunk3, 1, 512);
    chunk4 = get_next_chunk(chunk3);

    set_chunk_used(chunk2);
    set_chunk_used(chunk3);
    set_chunk_used(chunk4);

    // show_heap(heap, 1);
    coalesce_chunk(heap, chunk1);
    // show_heap(heap, 1);

    if (get_chunk_size(chunk1) != 512)
    {
        print_string("\nNO\n");
        return;
    }
    if (get_chunk_size(chunk2) != 512)
    {
        print_string("\nNO\n");
        return;
    }
    print_string("\nOK\n");
}

void case_segf(void)
{
    t_heap *heap;
    t_chunk *chunk1;
    t_chunk *chunk2;

    print_string("\nCOALESCE SEGF 1:\n");
    heap = arena_unshift(SMALL, get_heap_size(SMALL));
    chunk1 = get_first_chunk(heap);
    chunk1->forward = heap->size - sizeof(t_heap);
    chunk1->backward = 0;
    split_chunk(heap, chunk1, SMALL, 129952);
    chunk2 = get_next_chunk(chunk1);

    set_chunk_used(chunk2);
    show_heap(heap, 1);
    coalesce_chunk(heap, chunk2);
    show_heap(heap, 1);

    release_heap_maybe(heap, 1);
}

void test_coalesce(void)
{
    // t_heap *heap;
    // t_chunk *chunk1;
    // t_chunk *chunk2;
    // t_chunk *chunk3;

    // heap = arena_unshift(1, get_heap_size(1));
    // chunk1 = get_first_chunk(heap);
    // chunk1->forward = heap->size - sizeof(t_heap);
    // split_chunk(heap, chunk1, 1, 512);
    // chunk2 = get_next_chunk(chunk1);
    // split_chunk(heap, chunk2, 1, 512);
    // chunk3 = get_next_chunk(chunk3);

    //show_heap(heap, 1);
    //show_alloc_mem();
    // case_1();
    // case_2();
    // case_3();
    // case_4();
    // case_5();
    // case_6();
    // case_7();
    // case_8();
    case_segf();
}