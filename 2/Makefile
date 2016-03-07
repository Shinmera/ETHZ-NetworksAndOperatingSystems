
CFLAGS ?= -Wall
CC ?= clang

all: forktree ls-wrapper

forktree: forktree.c
	$(CC) $(CFLAGS) -o forktree.o forktree.c

ls-wrapper: ls-wrapper.c
	$(CC) $(CFLAGS) -o ls-wrapper.o ls-wrapper.c
