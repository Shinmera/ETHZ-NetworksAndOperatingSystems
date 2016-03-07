#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int level = 0;

void print_status(int n, int parent_p, pid_t parent, pid_t child){
  printf("%d %.*s>%.*s %c %d -> %d\n",
         n,
         level, "===",
         (3-level), "   ",
         (parent_p)?'P':'C',
         parent, child);
}

pid_t run_fork(int n){
  pid_t pid = fork();
  
  if(pid < 0){
    return -1;
  }else if(pid == 0){
    ++level;
    print_status(n, 0, getppid(), getpid());
  }else{
    print_status(n, 1, getpid(), pid);
    waitpid(pid, NULL, 0);
  }

  return pid;
}

int main(void){
  run_fork(1);
  run_fork(2);
  run_fork(3);
  return 0;
}
