#include "heap.h"
#include "rb_tree_42.h"

t_heap *rb_tree_heap_new(void *memory, size_t size)
{
    t_heap *heap;

    heap = get_heap(memory);
    heap->left = NULL;
    heap->right = NULL;
    heap->parent = NULL;
    heap->color = RED;
    heap->size = size;
    heap->size_max_free = size - sizeof(t_heap);
    return heap;
}