#include "rb_tree.h"

void insertFixup(t_rb_tree *t, t_rb_node *x)
{

    /*************************************
    *  maintain Red-Black t_rb_tree balance  *
    *  after inserting t_rb_node x           *
    *************************************/

    /* check Red-Black properties */
    while (x != t->root && x->parent->color == RED)
    {
        /* we have a violation */
        if (x->parent == x->parent->parent->left)
        {
            t_rb_node *y = x->parent->parent->right;
            if (y->color == RED)
            {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {

                /* uncle is BLACK */
                if (x == x->parent->right)
                {
                    /* make x a left child */
                    x = x->parent;
                    rotateLeft(t, x);
                }

                /* recolor and rotate */
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight(t, x->parent->parent);
            }
        }
        else
        {

            /* mirror image of above code */
            t_rb_node *y = x->parent->parent->left;
            if (y->color == RED)
            {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {

                /* uncle is BLACK */
                if (x == x->parent->left)
                {
                    x = x->parent;
                    rotateRight(t, x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft(t, x->parent->parent);
            }
        }
    }
    t->root->color = BLACK;
}
