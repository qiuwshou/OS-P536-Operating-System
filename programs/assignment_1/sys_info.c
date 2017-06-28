#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
  int id;
  int pid;
  char *arg = argv[1];
  int fd[2];
  char readbuffer[100];
  
  pipe(fd);
  id = fork();
  pid = getpid();  

  if(id == 0){
    printf("Child pid = %d\n", pid);
    close(fd[1]);
    read(fd[0],readbuffer,sizeof(readbuffer));
    char path[400];
    strcat(path,"/bin/");
    strcat(path,readbuffer);

    int ret = strcmp(readbuffer,"echo");
    if(ret == 0){
      execl(path,readbuffer,"Hello World!",(char*)0);      
      } 
    else{   
      execl(path,readbuffer,(char*)0);    
    }
    exit(0);      
  }
  else{
    printf("Parent pid = %d\n",pid);
    close(fd[0]);    
    write(fd[1],arg,(strlen(arg)+1));    
    exit(0);
  }
  
}
