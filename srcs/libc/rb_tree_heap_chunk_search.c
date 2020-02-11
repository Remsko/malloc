#include "chunk.h"
#include "rb_tree_42.h"

t_rb_tree *rb_tree_heap_chunk_search(t_rb_tree *root, t_chunk *chunk, int (*cmp_f)(t_chunk *, void *))
{
    t_rb_tree *iter;
    int diff;

    iter = root;
    while (iter != NULL)
    {
        diff = cmp_f(chunk, (void *)iter);
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
