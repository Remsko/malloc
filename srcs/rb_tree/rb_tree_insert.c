#include "rb_tree.h"

t_rb_node *insertNode(t_rb_tree *t, t_rb_node *x, int (*cmp)(t_rb_node *, t_rb_node *))
{
    t_rb_node *current, *parent;

    /***********************************************
    *  allocate t_rb_node for data and insert in tree  *
    ***********************************************/

    /* find where t_rb_node belongs */
    current = t->root;
    parent = 0;
    while (current != t->nil)
    {
        parent = current;
        current = cmp(x, current) ? current->left : current->right;
    }

    /* setup new t_rb_node */
    x->parent = parent;
    x->left = t->nil;
    x->right = t->nil;
    x->color = RED;

    /* insert t_rb_node in tree */
    if (parent)
    {
        if (cmp(x, parent))
            parent->left = x;
        else
            parent->right = x;
    }
    else
    {
        t->root = x;
    }

    insertFixup(t, x);
    return (x);
}
