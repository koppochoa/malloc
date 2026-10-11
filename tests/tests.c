#include "tests.h"

void run_tests(void)
{
    // simple_malloc();
    // multiple_malloc();
    // inbetween_malloc();
    // simple_calloc();
    simple_realloc();
}

void simple_malloc(void)
{
    printf("[Simple Malloc]\n");

    int *val = malloc(sizeof(int));
    *val = 42;

    if (!val)
    {
        printf("Error while allocating simple value\n");
    }
    else
    {
        printf("Allocated Value: %d\n", *val);
    }

    print_mem(regions);

    free(val);
}

void multiple_malloc(void)
{
    printf("[Multiple Malloc]\n");

    int *val = malloc(sizeof(int));
    *val = 42;
    char *val_char = malloc(sizeof(char) * 14);
    bool *val_bool = malloc(sizeof(bool));

    memcpy(val_char, "Hello, World?", 14);
    *val_bool = true;

    printf("Allocated Value: %d\n", *val);
    printf("Allocated Value: %s\n", val_char ? val_char : 0);
    printf("Allocated Value: %d\n", val_bool ? *val_bool : -1);

    print_mem(regions);

    free(val);
    free(val_char);
    free(val_bool);
}

void inbetween_malloc(void)
{
    printf("[In Between Malloc]\n");

    int *val = malloc(sizeof(int));
    *val = 42;
    char *val_char = malloc(sizeof(char) * 14);
    bool *val_bool = malloc(sizeof(bool));

    memcpy(val_char, "Hello, World?", 14);
    *val_bool = true;

    print_mem(regions);

    free(val_char);

    char *val_char2 = malloc(sizeof(char) * 14);
    memcpy(val_char, "Nahhh, World?", 14);

    print_mem(regions);
    dump_memory(&regions[0]);

    printf("New Value : %s\n", val_char2);

    free(val);
    free(val_bool);
    free(val_char2);
}

void simple_calloc(void)
{
    printf("[Simple Calloc]\n");

    int *val = malloc(sizeof(int));

    print_mem(regions);

    *val = 4839247;

    print_mem(regions);
    dump_memory(&regions[0]);

    free(val);
}

void simple_realloc(void)
{
    int *val = malloc(sizeof(int));

    val[0] = 10;

    print_mem(regions);

    printf("Val[0] : %d\n", val[0]);

    int *v2 = realloc(val, sizeof(int) * 2);

    v2[1] = 42;

    printf("Val[0] : %d | Val[1] : %d\n", v2[0], val[1]);

    print_mem(regions);
    dump_memory(&regions[0]);

    free(v2);
}
