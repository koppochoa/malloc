#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "malloc.h"

void dump_memory(struct Region *reg)
{
    FILE *file = fopen("memory_dump.bin", "wb");
    if (file == NULL)
    {
        perror("fopen");
        return;
    }

    fwrite(reg->ptr, 1, reg->len, file);

    fclose(file);
}

void print_mem(struct Region *reg)
{
    if (reg == NULL || reg->ptr == NULL)
        return;

    printf("\n");
    printf("+======================================================+\n");
    printf("|                  MEMORY REGION                       |\n");
    printf("+======================================================+\n");
    printf("| Base : %-18p Size : %-8zu bytes |\n", (void *)reg->ptr, reg->len);
    printf("+======================================================+\n");

    struct Block *block = reg->first;
    size_t index = 0;

    while (block != NULL)
    {
        printf("\n");
        printf("+------------------------------------------------------+\n");
        printf("| BLOCK %-3zu | %-10zu bytes | %-4s                  |\n",
               index, block->len, block->free ? "FREE" : "USED");
        printf("+------------------------------------------------------+\n");

        printf("| HEADER                                               |\n");
        printf("| len: %-10zu free: %-5s next: %p\n", block->len,
               block->free ? "true" : "false", (void *)block->next);
        printf("+------------------------------------------------------+\n");

        unsigned char *data = (unsigned char *)block + sizeof(struct Block);

        printf("| DATA (hex)                                           |\n");

        if (block->free)
        {
            printf(
                "| [ FREE SPACE ]                                       |\n");
        }
        else
        {
            for (size_t i = 0; i < block->len; i++)
            {
                if (i % 16 == 0)
                    printf("| ");

                printf("%02X ", data[i]);

                if (i % 16 == 15 || i == block->len - 1)
                    printf("\n");
            }
        }

        printf("+------------------------------------------------------+\n");

        block = block->next;
        index++;
    }

    printf("\n+======================================================+\n");
    printf("|                  END OF REGION                       |\n");
    printf("+======================================================+\n\n");
}
