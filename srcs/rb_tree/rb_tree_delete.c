#include "rb_tree.h"
#include <stdlib.h>

void deleteNode(t_rb_tree *t, t_rb_node *z)
{
    t_rb_node *x, *y;

    /*****************************
    *  delete t_rb_node z from tree  *
    *****************************/

    if (!z || z == t->nil)
        return;

    if (z->left == t->nil || z->right == t->nil)
    {
        /* y has a t->nil t_rb_node as a child */
        y = z;
    }
    else
    {
        /* find tree successor with a t->nil t_rb_node as a child */
        y = z->right;
        while (y->left != t->nil)
            y = y->left;
    }

    /* x is y's only child */
    if (y->left != t->nil)
        x = y->left;
    else
        x = y->right;

    /* remove y from the parent chain */
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        t->root = x;

    if (y != z)
        z->data = y->data;

    if (y->color == BLACK)
        deleteFixup(t, x);

    free(y);
}
