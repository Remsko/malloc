#include "../incs/malloc.h"

/*
** BLOCK:	[header][payload]
**			----------------- block_size	header + payload
**			--------          header_size	sizeof(t_block_header)
**			        --------- payload_size	rounded up to TINY, SMALL or aligned to page_size (size % 4096 == 0)
*/

inline t_block_header *get_block_header(void *start)
{
	return (t_block_header *)start;
}

t_block_header *new_block_header(void *start, size_t size)
{
	t_block_header *bh;

	bh = get_block_header(start);
	bh->total_size = size;
	bh->free = true;
	return bh;
}

inline t_block_header *get_block_header_from_payload(void *payload)
{
	return get_block_header(payload - sizeof(t_block_header));
}

inline void *get_block_payload_from_header(t_block_header *bh)
{
	return (void *)bh + sizeof(t_block_header);
}

inline t_block_header *get_next_block_header(t_block_header *bh)
{
	return get_block_header((void *)bh + bh->total_size);
}

inline size_t get_payload_size(t_block_header *bh)
{
	return bh->total_size - sizeof(t_block_header);
}