#include <xinu.h>
#include <future.h>


future_t* future_alloc(future_mode_t mode){
  future_t* myfuture;
  char* addr = getmem(sizeof(myfuture));
  
  if(addr != (char *)SYSERR){
    myfuture =(future_t *) addr;
    myfuture->state = FUTURE_EMPTY;
    myfuture->mode = mode;    
    myfuture->set_queue = initial_queue();
    myfuture->get_queue = initial_queue();
    return myfuture;
  }
  else{
    return NULL;
  }
}

