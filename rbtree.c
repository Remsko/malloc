/* red-black tree */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "rb_tree.h"
#include "heap.h"

typedef int T; /* type of item to be stored */
#define compLT(a, b) (*(int *)a < *(int *)b)
#define compEQ(a, b) (*(int *)a == *(int *)b)

/* Red-Black tree description */

/* all leafs are sentinels */

t_rb_node g_nil = {0, 0, 0, 0, BLACK};

typedef struct Tree3
{
    t_heap_tree tree1;
    t_heap_tree tree2;
    t_heap_tree tree3;
} Tree3;

t_heap_tree *init_tree()
{
    static Tree3 tree = {
        {.root = (t_heap_node *)&g_nil,
         .nil = (t_heap_node *)&g_nil},
        {.root = (t_heap_node *)&g_nil,
         .nil = (t_heap_node *)&g_nil},
        {.root = (t_heap_node *)&g_nil,
         .nil = (t_heap_node *)&g_nil}};

    return &tree.tree1;
}

int cmp_ptr(t_rb_node *n1, t_rb_node *n2)
{
    return (void *)n1 < (void *)n2;
}

int cmp_ptr_equal(t_rb_node *n1, t_rb_node *n2)
{
    return (void *)n1 == (void *)n2;
}

t_rb_node *findNode(t_rb_tree *t, void *data)
{

    /*******************************
    *  find node containing data  *
    *******************************/

    t_rb_node *current = t->root;
    while (current != t->nil)
        if (cmp_ptr_equal(data, current->data))
            return (current);
        else
            current = cmp_ptr(data, current->data) ? current->left : current->right;
    return (0);
}

void print_inorder(t_rb_tree *tree, t_rb_node *node)
{
    if (node == tree->nil)
        return;
    print_inorder(tree, node->left);
    printf("%p\n", (void *)node);
    print_inorder(tree, node->right);
}

int main(int argc, char **argv)
{
    int a, maxnum, ct;
    t_heap_tree *tree;
    t_rb_node *t;

    /* command-line:
     *
     *   rbt maxnum
     *
     *   rbt 2000
     *       process 2000 records
     *
     */

    tree = init_tree();
    maxnum = atoi(argv[1]);
    size_t *nb;

    nb = malloc(sizeof(size_t) * maxnum);
    for (ct = 0; ct < maxnum; ct++)
    {
        nb[ct] = ct;
        if ((t = findNode((t_rb_tree *)tree, &nb[ct])) != NULL)
        {
            deleteNode((t_rb_tree *)tree, t);
        }
        else
        {
            t_heap_node *x;
            if ((x = malloc(sizeof(*x))) == 0)
            {
                printf("insufficient memory (insertNode)\n");
                exit(1);
            }
            x->size = nb[ct];
            insertNode((t_rb_tree *)tree, (t_rb_node *)x, &cmp_ptr);
        }
    }
    for (ct = 1; ct < maxnum - 1; ct++)
    {
        if ((t = findNode((t_rb_tree *)tree, &nb[ct])) != NULL)
        {
            deleteNode((t_rb_tree *)tree, t);
        }
    }
    print_inorder((t_rb_tree *)tree, (t_rb_node *)tree->root);
    return 0;
}