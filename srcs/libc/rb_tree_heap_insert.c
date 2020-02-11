#include "rb_tree_42.h"
#include "heap.h"
#include "libc.h"

bool rb_tree_heap_insert(t_rb_tree **root, t_rb_tree *heap,
                         int (*cmp_f)(void *, void *))
{
    t_rb_tree *search;
    int diff;

    if (root == NULL)
        return (false);
    if (*root == NULL)
    {
        heap->color = BLACK;
        *root = heap;
        return (true);
    }
    search = rb_tree_heap_search(*root, heap, cmp_f);
    if ((diff = cmp_f((void *)heap, (void *)search)) == 0)
        return (false);
    heap->parent = search;
    if (diff < 0)
        search->left = heap;
    else
        search->right = heap;
    rb_tree_fixredred(root, heap);
    return (true);
}
