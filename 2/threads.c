#include "threads.h"

ucontext_t main_context;
struct queue_node *queue;
struct thread *current_thread;

struct queue_node{
  struct thread *thread;
  struct queue_node *prev;
  struct queue_node *next;
};

void thread_run_func(){
  current_thread->func(current_thread->arg);
  thread_exit();
}

struct thread *thread_create(void (*func)(void *), void *arg){
  struct thread *thread = calloc(1, sizeof(struct thread));

  if(thread == NULL)
    exit(1);
  
  if(getcontext(&thread->context) == -1)
    exit(2);

  thread->func = func;
  thread->arg = arg;
  thread->context.uc_stack.ss_sp = &thread->stack;
  thread->context.uc_stack.ss_size = sizeof(thread->stack);
  thread->context.uc_link = NIL;
  
  makecontext(&thread->context, &thread_run_func, 0);

  return thread;
}

void thread_add_runqueue(struct thread *thread){
  struct queue_node *node = calloc(1, sizeof(struct queue_node));
  if(node == NULL)
    exit(1);

  node->thread = thread;
  
  if(queue == NULL){
    node->next = node;
    node->prev = node;
    queue = node;
  }else{
    node->next = queue->next;
    node->prev = queue;
    queue->next->prev = node;
    queue->next = node;
    // Make head
    queue = node;
  }
}

void thread_exit(void){
  if(queue != NULL){
    struct queue_node *curr = queue;

    if(curr->next == curr->prev){
      queue = NULL;
    }else{
      // Scan the queue
      while(curr->thread != current_thread){
        curr = curr->next;
      }
      curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
    }

    free(curr->thread);
    free(curr);
    
    dispatch();
  }
}

void thread_yield(void){
  schedule();
  dispatch();
}

void dispatch(void){
  if(queue != NULL){
    struct thread *previous_thread = current_thread;
    current_thread = queue->thread;
    if(swapcontext(&previous_thread->context, &current_thread->context) == -1)
      exit(4);
  }
}

void schedule(void){
  if(queue != NULL){
    queue = queue->next;
  }
}

void thread_start_threading(void){
  if(queue != NULL){
    schedule();
    current_thread = queue->thread;
    if(swapcontext(&main_context, &current_thread->context) == -1)
      exit(4);
  }
}
