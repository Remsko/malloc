#include "chunk.h"
#include "memory.h"
#include "test.h"

t_chunk *dummy_new_chunk(size_t size)
{
    void *mem = get_some_memory(size);
    t_chunk *chk = (t_chunk *)mem;
    chk->forward = 4096;
    chk->free = 0;
    return chk;
}

void test_split_chunk(void)
{
    // case simple
    //
    putstr("Simple Split:");
    t_chunk *simple = dummy_new_chunk(4096);
    t_chunk *splitted = split_chunk(simple, 2, 256);
    if (splitted->forward != 256)
    {
        return putstr(" NO\n");
    }
    else
    {
        putstr(" OK");
    }
    splitted = (void *)splitted + splitted->forward;
    if (splitted->forward != (4096 - 256))
    {
        return putstr(" NO\n");
    }
    else
    {
        putstr(" OK");
    }
    putstr("\n");

    // case no space
    //
    putstr("No Space: ");
    t_chunk *nospace = split_chunk(simple, 2, 196);
    if (nospace->forward != 256)
    {
        return putstr(" NO\n");
    }
    else
    {
        putstr(" OK");
    }
    putstr("\n");

    // case space left
    //
    putstr("Space Left: ");
    t_chunk *spaceleft = split_chunk(splitted, 2, 512);
    if (spaceleft->forward != 512)
    {
        return putstr(" NO\n");
    }
    else
    {
        putstr(" OK");
    }
    spaceleft = (void *)spaceleft + spaceleft->forward;
    if (spaceleft->forward != (4096 - 256 - 512))
    {
        return putstr(" NO\n");
    }
    else
    {
        putstr(" OK");
    }
    // too much
    //
    putstr("Space Left: ");
    spaceleft = split_chunk(splitted, 2, 5012);
    if (spaceleft->forward != 512)
    {
        return putstr(" NO\n");
    }
    else
    {
        putstr(" OK");
    }
    putstr("\n");
}