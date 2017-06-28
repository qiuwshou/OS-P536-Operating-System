/* xsh_producer_consumer */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <delay.h>
int32 buff_size, buff_send,sent,received;
int max_delay;
sid32 mutex, item, space;

/*------------------------------------------------------------------------
 * xsh_producer_consumer
 *------------------------------------------------------------------------
 */
void prod(unsigned char buff,unsigned char counter){
  while(sent != 0){
    rand_delay(max_delay);
    wait(space);
    wait(mutex);
    //send in buff
    buff += 1;
    sent = sent -1;
    counter ++;
    printf("Producer:<0x%02x>\n",(unsigned char)counter);
    if(counter == 0xff){
      counter = 0x00;
    }
    signal(mutex);
    //signal(item);
  }
}

void con(unsigned char buff){
  while(received != buff_send){
    rand_delay(max_delay);
    //wait(item);
    wait(mutex);
    //consume buff
    buff ++;
    received += 1;
    printf("Consumer:<0x%02x>\n",(unsigned char)buff);
    signal(mutex);
    signal(space);
  }
}


shellcmd xsh_producer_consumer(int nargs, char *args[]) {
//int32 buff_size, buff_send, max_delay; 
//sid32 mutex, item, space;


  if(nargs == 4){
    buff_size = atoi(args[1]);
    buff_send = atoi(args[2]);
    max_delay = atoi(args[3]);  
  }  
  else{
    printf("incorrect number of argument\n");
  }

  unsigned char counter = 0x00;
  unsigned char buff = 0x00;
  received =0;
  sent = buff_send;

  
  mutex = semcreate(1);
  item = semcreate(0);
  space = semcreate(buff_size);

  resume(create(con,1024,20,"consumer",2,buff));
  resume(create(prod,1024,20,"producer",2,buff,counter));

  return 0;
}
