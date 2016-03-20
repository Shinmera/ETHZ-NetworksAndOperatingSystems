#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void parent(pid_t child){
  sleep(2);
  kill(child, SIGSTOP);
  sleep(2);
  kill(child, SIGCONT);
  sleep(2);
  kill(child, SIGTERM);
  sleep(2);
  kill(child, SIGTERM);
}

void child_sigterm(int sig){
  signal(SIGTERM, SIG_DFL);
}

void child(){
  int counter = 0;
  signal(SIGTERM, child_sigterm);
  while(1){
    ++counter;
    printf("%i\n", counter);
    sleep(1);
  }
}

int main(void){
  pid_t pid = fork();
  
  if(pid < 0){
    return -1;
  }else if(pid == 0){
    child();
  }else{
    parent(pid);
  }
  
  return 0;
}
