#ifndef MALLOC_H
#define MALLOC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>

#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

#define MAX_REGIONS 100

struct Block
{
    size_t len;
    bool free;
    struct Block *next;
    struct Region *org;
};

struct Region
{
    char *ptr;
    size_t len;
    struct Block *first;
    int used;
};

extern int regions_count;
extern struct Region regions[MAX_REGIONS];
extern bool initialized;

void *malloc(size_t size);
void free(void *ptr);

void *realloc(void *ptr, size_t size);
void *calloc(size_t nmemb, size_t size);

struct Region create_region(size_t size);
char *available_region(size_t size);

struct Block *create_block(char *addr, size_t size, struct Block *next,
                           struct Region *org);

void init_mem(void);
size_t toPageSize(size_t size);
void *available(struct Region *region, size_t size);
void* can_realloc(struct Block* block, size_t size);
int free_region(struct Region *reg);
void dump_memory(struct Region *reg);
void print_mem(struct Region *reg);

#endif // MALLOC_H
