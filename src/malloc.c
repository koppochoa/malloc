#include "malloc.h"

#include <stdio.h>

struct Region regions[MAX_REGIONS] = { 0x0 };
int regions_count = 0;
bool initialized = false;

void *malloc(size_t size)
{
    if (!initialized)
    {
        init_mem();
    }

    char *memspace = available_region(size);

    return memspace;
}

void *calloc(size_t nmemb, size_t size)
{
    char *memspace = malloc(nmemb * size);

    if (!memspace)
        return NULL;

    for (size_t i = 0; i < nmemb * size; i++)
    {
        memspace[i] = 0;
    }

    return memspace;
}

void *realloc(void *ptr, size_t size)
{
    if (!ptr)
        return NULL;

    struct Block *md = (struct Block *)((char *)ptr - sizeof(struct Block));

    void *res = can_realloc(md, size);

    if (!res)
    {
        void *new = malloc(size);
        memcpy(new, ptr, md->len);

        if (!new)
        {
            return NULL;
        }

        free(ptr);
        return new;
    }

    return res;
}

void free(void *ptr)
{
    struct Block *md = (struct Block *)((char *)ptr - sizeof(struct Block));

    if (md->org->used == 1)
    {
        free_region(md->org);
    }

    md->free = true;
}
