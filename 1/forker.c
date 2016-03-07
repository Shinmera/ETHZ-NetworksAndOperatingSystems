#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void){
  pid_t childPID = fork();

  if(childPID < 0){
    return 1;
  }else if(childPID == 0){
    printf("I'm the child and my PID is %d\n", getpid());
  }else{
    printf("I'm the parent and my child's PID is %d\n", childPID);
  }
    
  return 0;
}
