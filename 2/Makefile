
CFLAGS ?= -Wall
CC ?= clang

all: forktree ls-wrapper zombie

forktree: forktree.c
	$(CC) $(CFLAGS) -o forktree.o forktree.c

ls-wrapper: ls-wrapper.c
	$(CC) $(CFLAGS) -o ls-wrapper.o ls-wrapper.c

zombie: zombie.c
	$(CC) $(CFLAGS) -o zombie.o zombie.c

threads: threads-test.c threads.h threads.c
	$(CC) $(CFLAGS) -o threads.o threads.c threads-test.c
