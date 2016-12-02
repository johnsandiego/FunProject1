#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {
  int i, pid;
  char* args[2];
  printf("my name is %s. my pid is %d. then will forks\n\n", argv[0], getpid());
  pid = fork();
  printf("%d\n",pid );
  if(pid==0){


    args[0] = "program1.out";
    args[1] = "9";
    args[2] =  NULL;
    execv(args[0], args);
  }
  else{
    wait(NULL);
    printf("I am the parent. my name is %s. my PID is %d \n",argv[0],getpid() );
  }
  return 0;
}
