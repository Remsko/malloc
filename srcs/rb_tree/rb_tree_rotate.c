#include "rb_tree.h"

void rotateLeft(t_rb_tree *t, t_rb_node *x)
{
    t_rb_node *y;

    y = x->right;
    x->right = y->left;
    if (y->left != t->nil)
        y->left->parent = x;
    if (y != t->nil)
        y->parent = x->parent;
    if (x->parent)
    {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    else
    {
        t->root = y;
    }
    y->left = x;
    if (x != t->nil)
        x->parent = y;
}

void rotateRight(t_rb_tree *t, t_rb_node *x)
{
    t_rb_node *y;

    y = x->left;
    x->left = y->right;
    if (y->right != t->nil)
        y->right->parent = x;
    if (y != t->nil)
        y->parent = x->parent;
    if (x->parent)
    {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    }
    else
    {
        t->root = y;
    }
    y->right = x;
    if (x != t->nil)
        x->parent = y;
}