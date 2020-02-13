#include "heap.h"
#include "chunk.h"
#include "arena.h"
#include "malloc.h"
#include "libc.h"

#include "ft_printf.h"

t_chunk *search_free_chunk(t_heap_node *heap, size_t size)
{
    t_chunk *chunk;

    if (heap == NULL)
        return NULL;
    chunk = get_first_chunk(heap);
    while (chunk_is_on_heap(heap, chunk))
    {
        if (chunk_is_available(chunk, size))
        {
            split_chunk(heap, chunk, size);
            return chunk;
        }
        chunk = get_next_chunk(chunk);
        //ft_printf("loop inf");
    }
    return NULL;
}

t_chunk *search_free_chunk_disorder(t_heap_tree *tree, t_heap_node *node, size_t size)
{
    t_chunk *chunk;

    //ft_printf("search");
    if (node == tree->nil)
        return NULL;
    if ((chunk = search_free_chunk_disorder(tree, node->right, size)))
        return chunk;
    if ((chunk = search_free_chunk(node, size)))
        return chunk;
    if ((chunk = search_free_chunk_disorder(tree, node->left, size)))
        return chunk;
    return NULL;
}

// bool search_chunk(t_chunk *chunk, t_heap ***head_fnd, t_heap **heap_fnd)
// {
//     t_heap **heap_head;
//     t_heap *heap_maybe;

//     for (t_config_type type = 0; type < TYPES; type++)
//     {
//         heap_head = get_arena_heap_head(type);
//         if (heap_head != NULL)
//         {
//             heap_maybe = (t_heap *)rb_tree_heap_chunk_search((t_rb_tree *)*heap_head, chunk, &chunk_cmp);
//             if (heap_maybe != NULL)
//             {
//                 if (chunk_is_on_heap(heap_maybe, chunk))
//                 {
//                     *head_fnd = heap_head;
//                     *heap_fnd = heap_maybe;
//                     return true;
//                 }
//             }
//         }
//     }
//     return false;
// }

int chunk_cmp(t_chunk *chunk, t_heap_node *heap)
{
    return (void *)chunk < (void *)heap;
}

void show_heap(t_heap_node *heap, t_config_type type);

bool search_chunk(t_chunk *chunk, t_heap_tree **tree_fnd, t_heap_node **heap_fnd)
{
    t_heap_tree *t;
    t_heap_node *current;

    (void)heap_fnd;
    (void)tree_fnd;
    for (t_config_type type = 0; type < TYPES; type++)
    {
        //ft_printf("loop start 2\n");
        t = get_arena_heap_tree(type);
        current = t->root;
        //ft_printf("loop start\n");
        while (current != t->nil)
        {
            //show_heap(current, type);
            //ft_printf("%p\n", current);

            //ft_printf("inside loop start %zu\n", current->size);
            //ft_printf("yolo\n");
            //ft_printf("after print %u\n", (chunk_is_on_heap(current, chunk)));
            if (chunk_is_on_heap(current, chunk))
            {
                //ft_printf("found!\n", current->size);
                *tree_fnd = t;
                *heap_fnd = current;
                return true;
            }
            else
            {
                //ft_printf("inside move\n");
                current = chunk_cmp(chunk, current) ? current->left : current->right;
                //ft_printf("after moving %p\n", current);
            }
            //ft_printf("inside loop end\n");
        }
        //ft_printf("loop end\n");
    }
    return false;
}