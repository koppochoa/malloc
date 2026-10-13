#ifndef TESTS_H
#define TESTS_H

#include "malloc.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void run_tests(void);

// malloc tests

void simple_malloc(void);
void multiple_malloc(void);
void inbetween_malloc(void);

// calloc tests

void simple_calloc(void);


// realloc tests

void simple_realloc(void);
void advanced_realloc(void);

void dump_memory(struct Region *reg);
void print_mem(struct Region *reg);

#endif // TESTS_H
