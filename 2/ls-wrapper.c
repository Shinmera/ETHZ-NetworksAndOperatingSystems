#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define PIPE_READ 0
#define PIPE_WRITE 1
#define STDOUT 1
#define STDERR 2

void call_ls(){
  static char *args[] = {"-l"};
  execvp("ls", args);
  exit(3);
}

int main(){
  int stdout_pipe[2];

  if(pipe(stdout_pipe) < 0){
    exit(1);
  }

  
  pid_t ls_pid = fork();  
  if(ls_pid < 0){
    close(stdout_pipe[PIPE_READ]);
    close(stdout_pipe[PIPE_WRITE]);
    exit(2);
  }else if(ls_pid == 0){
    dup2(stdout_pipe[PIPE_WRITE], STDOUT);
    dup2(stdout_pipe[PIPE_WRITE], STDERR);
    close(stdout_pipe[PIPE_READ]);
    close(stdout_pipe[PIPE_WRITE]);
    call_ls();
  }else{
    close(stdout_pipe[PIPE_WRITE]);
    printf("  Running `ls -l` at %d:\n", ls_pid);
    waitpid(ls_pid, NULL, 0);
    char buffer[512] = {0};
    while(read(stdout_pipe[PIPE_READ], buffer, sizeof(buffer)) != 0){
      printf("%s", buffer);
    }
    close(stdout_pipe[PIPE_READ]);
  }
}
