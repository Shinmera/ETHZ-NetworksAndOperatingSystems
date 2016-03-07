#ifndef THREADS_H_
#define THREADS_H_

#include <ucontext.h>
#include <stdlib.h>

#define STACK_SIZE 16384

struct thread{
  void (*func)(void *arg);
  void *arg;
  ucontext_t context;
  char stack[STACK_SIZE];
};

struct thread *thread_create(void (*func)(void *), void *arg);
void thread_add_runqueue(struct thread *thread);
void thread_yield(void);
void dispatch(void);
void schedule(void);
void thread_exit(void);
void thread_start_threading(void);

#endif // THREADS_H_
