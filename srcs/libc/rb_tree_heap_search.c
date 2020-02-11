#include "heap.h"
#include "rb_tree_42.h"

t_rb_tree *rb_tree_heap_search(t_rb_tree *root, t_rb_tree *heap,
                               int (*cmp_f)(void *, void *))
{
    t_rb_tree *iter;
    int diff;

    iter = root;
    while (iter != NULL)
    {
        diff = cmp_f((void *)heap, (void *)iter);
        if (diff < 0)
        {
            if (iter->left == NULL)
                break;
            else
                iter = iter->left;
        }
        else if (diff == 0)
            break;
        else
        {
            if (iter->right == NULL)
                break;
            else
                iter = iter->right;
        }
    }
    return (iter);
}
