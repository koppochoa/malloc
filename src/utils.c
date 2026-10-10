#include "malloc.h"

void init_mem(void)
{
    printf("init called\n");

    for (int i = 0; i < MAX_REGIONS; i++)
    {
        regions[i].ptr = NULL;
        regions[i].first = NULL;
        regions[i].len = 0;
        regions[i].used = 0;
    }
    initialized = true;
}

size_t toPageSize(size_t size)
{
    size_t pages = size / 4096;

    if (size % 4096 != 0)
        pages++;

    return pages * 4096;
}

// Rechercher si un espace present assez grand pour acceuillir data

void *available(struct Region *region, size_t size)
{
    size_t aligned_size = ALIGN(size);

    if (aligned_size + sizeof(struct Block) > region->len)
        return NULL;

    struct Block *first = region->first;

    // region vide
    if (first == NULL)
    {
        printf("First Element\n");
        struct Block *newblock =
            create_block(region->ptr, aligned_size, NULL, region);
        region->first = newblock;

        region->used++;

        return (char *)newblock + sizeof(struct Block);
    }

    while (first)
    {
        struct Block *next = first->next;

        // Freed block
        if (first->free == true && first->len >= aligned_size)
        {
            printf("Using Freed Element\n");

            first->len = aligned_size;
            first->free = false;

            region->used++;

            return (char *)first + sizeof(struct Block);
        }

        char *block_end = ((char *)first + sizeof(struct Block) + first->len);
        if (!next)
        {
            size_t offset = (size_t)(block_end - region->ptr);
            size_t delta = region->len - offset;

            if (delta >= aligned_size + sizeof(struct Block))
            {
                printf("Added Next to End\n");

                // taille ok , creer nouveau block

                struct Block *newblock =
                    create_block(block_end, aligned_size, NULL, region);

                first->next = newblock;

                region->used++;

                return (char *)newblock + sizeof(struct Block);
            }
        }
        else
        {
            size_t delta = (size_t)((char *)next - block_end);

            if (delta >= aligned_size + sizeof(struct Block))
            {
                printf("Added Between\n");

                // taille ok , creer nouveau block

                struct Block *newblock =
                    create_block(block_end, aligned_size, next, region);
                first->next = newblock;

                region->used++;

                return (char *)newblock + sizeof(struct Block);
            }
        }

        first = next;
    }

    return NULL;
}

int free_region(struct Region *reg)
{
    int res = munmap(reg->ptr, reg->len);
    reg->first = NULL;
    reg->len = 0;
    reg->ptr = NULL;
    reg->used = 0;
    return res;
}
