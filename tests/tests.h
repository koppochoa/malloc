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

#endif // TESTS_H