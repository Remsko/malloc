#ifndef RB_TREE
#define RB_TREE

typedef enum e_node_color
{
    BLACK,
    RED
} t_node_color;

typedef struct s_rb_node
{
    struct s_rb_node *left;
    struct s_rb_node *right;
    struct s_rb_node *parent;
    void *data;
    t_node_color color;
} t_rb_node;

typedef struct s_rb_tree
{
    t_rb_node *root;
    t_rb_node *nil;
} t_rb_tree;

extern t_rb_node g_nil; // = {0, 0, 0, 0, BLACK};

void rotateLeft(t_rb_tree *t, t_rb_node *x);
void rotateRight(t_rb_tree *t, t_rb_node *x);

void insertFixup(t_rb_tree *t, t_rb_node *x);
t_rb_node *insertNode(t_rb_tree *t, t_rb_node *x, int (*cmp)(t_rb_node *, t_rb_node *));

void deleteFixup(t_rb_tree *t, t_rb_node *x);
void deleteNode(t_rb_tree *t, t_rb_node *z);

#endif