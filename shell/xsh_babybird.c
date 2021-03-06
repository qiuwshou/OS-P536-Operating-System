
/* xsh_babybird */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <a6.h>
/*------------------------------------------------------------------------
 * xsh_babybird
 *------------------------------------------------------------------------
 */

int32 num_babies,num_fetch,num_eat;
int32 bowl;
int x,y;
void baby(struct cond_t* cv, struct mutex_t* mutex){
  mutex_lock(mutex);
  //printf("mutex %d\n",mutex->count);
  while (bowl == 0){
    cond_wait(cv,mutex);
  }  
  bowl = bowl - 1;
  printf("baby bird %d ate a worm!(%d total).\n",y,x);
 
  mutex_unlock(mutex);
  //printf("mutex %d\n",mutex->count);
}

void parent(struct cond_t* cv,struct mutex_t* mutex){
  mutex_lock(mutex);
  //printf("mutex %d\n",mutex->count);
  while(bowl == 0){
    bowl = num_fetch;
    cond_signal(cv);
    printf("Parent bird filled the dish with %d worms!\n",num_fetch);
  }
  mutex_unlock(mutex);
  //printf("mutex %d\n",mutex->count);
}

shellcmd xsh_babybird(int nargs, char *args[]) {
  struct mutex_t mutex;
  struct cond_t cv;
  mutex_create(&mutex);
  cond_init(&cv);
  int32 i; 

  if(nargs == 2 || nargs == 7){
    for(i = 1; i < nargs; i=i+2){
      if(strncmp(args[i],"-b",20) ==0  || strncmp(args[i],"--babies",20) == 0){
	num_babies = atoi(args[i+1]);
      }
      else if(strncmp(args[i],"-e",20) ==0 || strncmp(args[i],"--eat",20) == 0){
	num_eat = atoi(args[i+1]);
      }
      else if(strncmp(args[i],"-f",20) == 0 || strncmp(args[i],"--fetch",20) == 0){
	num_fetch = atoi(args[i+1]);
      }
      else if(strncmp(args[i],"--help",20) == 0 || strncmp(args[i],"-h",20) == 0){
	printf("Usage: %s\n\n", args[0]);
	printf("Description:\n");
	printf("\t The number of fetch worm --fetch or -f\n");
	printf("\t The number of eat worm --eat or -e\n");
	printf("\t the number of baby birds --babies or -b\n");
	printf("\t Useful help text --help or -h\n");
      }
      
    }
  }
  else{
    printf("wrong number of argument. type -h or --help for m\
ore details\n");
  }

  bowl = num_fetch;

  //printf("f:%d e:%d b:%d\n", num_fetch,num_eat,num_babies);
  for(x = 1; x<=num_eat; x++){
    for(y = 1; y<=num_babies; y++){
      //printf("i:%d j:%d\n",i,j);
      resume(create(baby,1024,20,"baby",2,cv,mutex));
      resume(create(parent,1024,20,"parent",2,cv,mutex));
    }
  }
  printf("%d worms left.\n",bowl);
 
  return 0;
}
