/* xsh_dining_philosophers */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <delay.h>
int32 num_p, num_c;
int max_delay;
sid32 footman,mutex;

/*------------------------------------------------------------------------
 * xsh_dining_philosophers
 *------------------------------------------------------------------------
 */
void get_fork(int32 num, sid32 fork[], int32 state[]){
  wait(mutex);
  wait(fork[num]);
  wait(fork[(num+1)%num_p]);
  state[num] = 1; 
  signal(mutex);  
}

void give_fork(int32 num, sid32 fork[],int32 state[]){
  wait(mutex);
  signal(fork[num]);
  signal(fork[(num+1)%num_p]);  
  state[num] = 0;
  signal(mutex);
}

void philosopher(int32 num, int32 cyc,sid32 fork[],int32 state[]){
  char *s;
  wait(footman);  
  if(state[(num+1)%num_p] != 1 && state[(num-1)%num_p] !=1){
    //can eat
    get_fork(num,fork,state);
    rand_delay(max_delay);
    if(state[num] == 0){
      s = "thinking";
    }
    else{ 
      s = "eating";
    }
    printf("Philosopher<number:%d><state:%s><cycle:%d>\n",num,s,cyc);
    give_fork(num,fork,state);
  }
  else{
    //cant eat can be hungry
    rand_delay(max_delay);
    if(state[num] == 0){
      s = "thinking";
    }
    else{
      s = "eating";
    }
    printf("Philosopher<number:%d><state:%s><cycle:%d>\n",num,s,cyc);
  }
  signal(footman);
}


shellcmd xsh_dining_philosophers(int nargs, char *args[]) {

  if(nargs == 4){
    num_p = atoi(args[1]);
    num_c = atoi(args[2]);
    max_delay = atoi(args[3]);
  }  
  else{
    printf("incorrect number of argument\n");
  }
  
  int32 i,j;
  int32 state[num_p];//0-thinking,1-eating
  footman = semcreate(1);
  sid32 fork[num_p];

  for(i=0;i<num_p;i++){
    fork[i] = semcreate(1);
    state[i] = 0;
  }
  
  mutex = semcreate(1);
  for(i=0;i<num_c;i++){
    for(j=0;j<num_p;j++){
      resume(create(philosopher,1024,20,"philosopher",4,j,i,fork,state));
    }
  }

  return 0;
}
