/* xsh_producer_consumer */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <delay.h>
int32 num_w, num_r,w_c, r_c;
int max_delay;
sid32 room, r, force;

/*------------------------------------------------------------------------
 * xsh_producer_consumer
 *------------------------------------------------------------------------
 */
void reader(int32 num, int32 cyc){

  //rand_delay(max_delay);
  //must wait for writer to finish
  wait(force);
  signal(force);
  
  wait(r);
  wait(room);
  rand_delay(max_delay);
  printf("<Reader><reader number:%d><cycle number:%d>\n",num,cyc);
  signal(room);
  signal(r);  

}

void writer(int32 num, int32 cyc){
  
  //rand_delay(max_delay);
  wait(force);
  wait(room);
  rand_delay(max_delay);
  printf("<Writer><writer number:%d><cycle number:%d>\n",num,cyc);
  signal(room);
  signal(force);

}


shellcmd xsh_readers_writers(int nargs, char *args[]) {

  int32 j,i,x,y;
  if(nargs == 6){
    num_w = atoi(args[1]);
    num_r = atoi(args[2]);
    w_c = atoi(args[3]);  
    r_c = atoi(args[4]);
    max_delay = atoi(args[5]);
  }  
  else{
    printf("incorrect number of argument\n");
  }

  r = semcreate(num_r);
  room = semcreate(1);
  force = semcreate(1);

  for(i=0;i<r_c;i++){
    for(j=0;j<num_r;j++){
      resume(create(reader,1024,20,"reader",2,j,i));
    }
  }

  for(x=0;x<w_c;x++){
    for(y=0;y<num_w;y++) {
      resume(create(writer,1024,20,"writer",2,y,x));
    }
  }
  return 0;
}
