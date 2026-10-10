CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla -Iinclude -g -O0
LDFLAGS=

TESTS_SRCS=$(shell find tests -name '*.c')
TESTS_OBJS=$(patsubst tests/%.c, tests_build/%.o, $(TESTS_SRCS))

SRCS=$(shell find src -name '*.c')
OBJS=$(patsubst src/%.c, build/%.o, $(SRCS))

TARGET=libmalloc.so

lib: $(OBJS)
	$(CC) -shared -o $(TARGET) $^ $(LDFLAGS)

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

tests: $(TESTS_OBJS)
	$(CC) -o testsuite $^ -L. -lmalloc

tests_build/%.o: tests/%.c
	mkdir -p $(dir $@)
	$(CC) -Iinclude -O0 -g -c $< -o $@

clean: 
	rm -r build
	rm $(TARGET)

.PHONY: lib tests clean
