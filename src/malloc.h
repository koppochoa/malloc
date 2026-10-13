#ifndef MALLOC_H
#define MALLOC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

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
    size_t used;
};

extern int regions_count;
__attribute__((visibility("default")))  extern struct Region regions[MAX_REGIONS];
extern bool initialized;

__attribute__((visibility("default"))) void *malloc(size_t size);
__attribute__((visibility("default"))) void free(void *ptr);
__attribute__((visibility("default"))) void *realloc(void *ptr, size_t size);
__attribute__((visibility("default"))) void *calloc(size_t nmemb, size_t size);

struct Region create_region(size_t size);
char *available_region(size_t size);

struct Block *create_block(char *addr, size_t size, struct Block *next,
                           struct Region *org);

void init_mem(void);
size_t toPageSize(size_t size);
void *available(struct Region *region, size_t size);
void *can_realloc(struct Block *block, size_t size);
int free_region(struct Region *reg);



#endif // MALLOC_H
