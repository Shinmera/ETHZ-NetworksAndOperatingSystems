#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

void print_ppid(){
  printf("Parent: %d\n", getppid());
}

int main(void){
  pid_t pid = fork();
  
  if(pid < 0){
    return -1;
  }else if(pid == 0){
    print_ppid();
    while(1){
      print_ppid();
      sleep(1);
    }
  }else{
    sleep(2);
  }
  return 0;
}
