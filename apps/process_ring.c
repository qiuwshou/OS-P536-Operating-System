//funcion defines
#include <xinu.h>
#include <process_ring.h>
void work(int32 e, int32 r, int32 value[], sid32 mutex){
  wait(mutex);
  printf("Ring element:%d, Round:%d, Value:%d\n",e,r,value[e]);
  int32 size = sizeof(value);
  value[(e+1)%size]=value[e] - 1;
  signal(mutex);
}

void hang(int32 e, int32 r, int32 value[], sid32 mutex){
  wait(mutex);
  printf("Ring element:%d, Round:%d, Value:%d\n",e,r,value[e]);
  int32 size = sizeof(value);
  value[(e+1)%size]=value[e] - 1;
  if(e !=2 ){
    signal(mutex);
  }    
}

void loop(int32 e, int32 r, int32 value[], sid32 mutex){
  /**wait(mutex);
  printf("Ring element:%d, Round:%d, Value:%d\n",e,r,value[e]);
  int32 size = sizeof(value);
  value[(e+1)%size]=value[e];
  sigenal(mutex);*/
  printf("Ring element:%d, Round:%d, Value:%d\n",e,r,value[e]);
  while(1){

  }
}

void chaos(int32 e, int32 r, int32 value[], sid32 mutex){
  wait(mutex);
  printf("Ring element:%d, Round:%d, Value:%d\n",e,r,value[e]);
  int32 size = sizeof(value);
  value[(e+1)%size]=value[e] - 1;
  signal(mutex);
}
