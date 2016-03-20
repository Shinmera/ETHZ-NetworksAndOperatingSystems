#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int threads = 0;
int counter = 0;
int lockvar = 0;

void lock(int threadid){
  asm volatile("1:\n\t"
               "movl $0, %%eax\n\t"
               "lock cmpxchg %2, %0\n\t"
               "test %%eax,%%eax\n\t"
               "jnz 1b"
               :"=m"(lockvar)
               :"r"(lockvar),"r"(threadid)
               :"memory", "eax");
}

void unlock(int threadid){
  if(threadid != lockvar)
    printf("WTF! Am %i but found %i!\n", threadid, lockvar);
  lockvar = 0;
}

void *incrementor(void *arg){
  int threadid = *(int*)arg;
  for(int i=0; i<1000000; ++i){
    lock(threadid);
    ++counter;
    unlock(threadid);
  }

  return NULL;
}

void create_thread(pthread_t *thread, void *(*func)(void *)){
  ++threads;
  if(pthread_create(thread, NULL, func, &threads)){
    exit(1);
  }
}

void join_thread(pthread_t *thread){
  if(pthread_join(*thread, NULL)){
    exit(2);
  }
}

int main(void){
  pthread_t thread0, thread1;
  
  create_thread(&thread0, incrementor);
  create_thread(&thread1, incrementor);
  join_thread(&thread0);
  join_thread(&thread1);

  printf("Counter: %i\n", counter);
  
  return 0;
}
