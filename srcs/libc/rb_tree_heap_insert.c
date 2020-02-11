#include "heap.h"
#include "rb_tree_42.h"

bool rb_tree_insert(t_rb_tree **root, t_rb_tree *heap,
                    int (*cmp_f)(t_rb_tree *, t_rb_tree *))
{
    t_rb_tree *new_node;
    t_rb_tree *search;
    int diff;

    if (root == NULL)
        return (false);
    if (*root == NULL)
    {
        new_node->color = BLACK;
        *root = new_node;
        return (true);
    }
    search = rb_tree_search(*root, heap, cmp_f);
    if ((diff = cmp_f(heap, search)) == 0)
    {
        free(new_node);
        return (false);
    }
    new_node->parent = search;
    if (diff < 0)
        search->left = new_node;
    else
        search->right = new_node;
    rb_tree_fixredred(root, new_node);
    return (true);
}
