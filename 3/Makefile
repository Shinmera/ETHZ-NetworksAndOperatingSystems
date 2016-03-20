
CFLAGS ?= -Wall
CC ?= clang

all: signals simple-lock

signals: signals.c
	$(CC) $(CFLAGS) -o signals.o signals.c

simple-lock: simple-lock.c
	$(CC) $(CFLAGS) -lpthread -o simple-lock.o simple-lock.c
