#include "malloc.h"

struct Region create_region(size_t size)
{
    struct Region res;

    size_t len = toPageSize(size);
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (ptr == MAP_FAILED)
    {
        res.ptr = NULL;
        return res;
    }

    res.ptr = ptr;
    res.len = len;
    res.first = NULL;

    regions_count++;

    return res;
}

char *available_region(size_t size)
{
    int i = 0;

    while (i < MAX_REGIONS && regions[i].ptr)
    {
        char *mem = available(regions + i, size);
        if (mem)
        {
            return mem;
        }

        i++;
    }

    if (i < MAX_REGIONS)
    {
        regions[i] = create_region(size);
        return available(regions + i, size);
    }

    return NULL;
}
