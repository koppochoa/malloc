#include "malloc.h"

struct Block *create_block(char *addr, size_t size, struct Block *next,
                           struct Region *org)
{
    struct Block *newblock = (struct Block *)addr;
    newblock->len = size;
    newblock->free = false;

    newblock->next = next;
    newblock->org = org;

    return newblock;
}
