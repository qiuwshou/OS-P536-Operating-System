#include <xinu.h>
#include <future.h>


future_t* future_alloc(future_mode_t mode){
  intmask mask = disable();
  future_t* myfuture;
  char* addr = getmem(sizeof(myfuture));

  if(addr != (char *)SYSERR){
    myfuture =(future_t *) addr;
    myfuture->state = FUTURE_EMPTY;
    myfuture->mode = mode;
    myfuture->set_queue = initial_queue();
    myfuture->get_queue = initial_queue();
    restore(mask);
    return myfuture;
  }
  else{
    restore(mask);
    return NULL;
  }
}

syscall future_get(future_t* f, int* value){
  intmask mask = disable();
  //pid32 pid = getpid();
  if(f->mode == FUTURE_EXCLUSIVE){
    while(f->state != FUTURE_READY){// if value not set yet
      wait(ex);
      f->pid = getpid();
      f->state = FUTURE_WAITING;
      signal(ex);
      suspend(f->pid);
      *value = f->value;
      restore(mask);
      return OK;
    }
    wait(ex);
    *value = f->value;
    f->state = FUTURE_EMPTY;
    signal(ex);
    restore(mask);
    return OK;
  }


  else if(f->mode == FUTURE_SHARED){
    while(f->state != FUTURE_READY){//value not set yet
      f->state = FUTURE_WAITING;
      f->pid = getpid();
      fenqueue(f->get_queue,f->pid);
      suspend(f->pid);
      *value=f->value;
    }
    *value=f->value;
   
    future_free(f);
    restore(mask);
    return OK;
  }


  else if(f->mode == FUTURE_QUEUE){
    pid32 pid= getpid();
    /*if(f->state == FUTURE_EMPTY){
      wait(get);
      fenqueue(f->get_queue,pid);
      f->state = FUTURE_WAITING;
      signal(get);
      suspend(pid);
      *value = f->value;
      restore(mask);
      return OK;
    }
    else if(f->state == FUTURE_WAITING){
      if(is_empty(f->set_queue) == 1){//set queue is empty
	wait(get);
	fenqueue(f->get_queue,pid);
	signal(get);
	suspend(pid);
	*value = f->value;
	restore(mask);
	return OK;
      }
      else{
	wait(get);
	pid = fdequeue(f->set_queue);
	signal(get);
	resume(pid);
	*value = f->value;
	restore(mask);
	return OK;
      }
    }
    else if(f->state == FUTURE_READY){
      if(is_empty(f->set_queue) == 1){//set queue empty
	wait(get);
	fenqueue(f->get_queue,pid);
	f->state = FUTURE_WAITING;
	signal(set);
	suspend(pid);
	*value = f->value;
	restore(mask);
	return OK;
      }
      else{
	wait(get);
	pid  = fdequeue(f->set_queue);
	signal(set);
	resume(pid);
	*value = f->value;
	restore(mask);
	return OK;
      }
      }*/
    if(is_empty(f->set_queue) == 1){
      wait(get);
      fenqueue(f->get_queue,pid);
      printf("pid %d", pid);
      signal(get);
      suspend(pid);
      *value = f->value;
      restore(mask);
      return OK;
    }
    else{
      wait(get);
      pid = fdequeue(f->set_queue);
      signal(get);
      resume(pid);
      restore(mask);
      return OK;
    }
  }
  

  else{    
    restore(mask);
    return SYSERR;
  }

}

syscall future_set(future_t* f, int value){
  intmask mask = disable();
  if(f->mode == FUTURE_EXCLUSIVE){
    while(f->state != FUTURE_READY){
      wait(ex);
      f->value = value;
      f->state = FUTURE_READY;
      signal(ex);
      resume(f->pid);
    }
    restore(mask);
    return OK;
  }


  else if(f->mode == FUTURE_SHARED){
 
    while( is_empty(f->get_queue) == 0){
      f->state = FUTURE_READY;
      f->value = value;
      pid32 pid = fdequeue(f->get_queue);
      resume(pid);
    }
    restore(mask);
    return OK;
  }


  else if(f->mode == FUTURE_QUEUE){
    pid32 pid=getpid();
    /* if(f->state == FUTURE_EMPTY){
      wait(set);
      fenqueue(f->set_queue,pid);
      f->state = FUTURE_READY;
      signal(set);
      suspend(pid);
      f->value = value;
      restore(mask);
      return OK;
    }
    else if(f->state == FUTURE_WAITING){
      if(is_empty(f->get_queue) == 1){ //get queue empty
	wait(set);
	fenqueue(f->set_queue,pid);
	f->state = FUTURE_READY;
	signal(set);
	suspend(pid);
	f->value = value;
	restore(mask);
	return OK;
      }
      else{
	wait(set);
	pid = fdequeue(f->get_queue);
	f->value = value;
	signal(set);
	resume(pid);
	restore(mask);
	return OK;
	}
    }
    else if(f->state == FUTURE_READY){
      wait(set);
      fenqueue(f->set_queue,pid);
      signal(set);
      suspend(pid);
      f->value = value;
      restore(mask);
      return OK;
      }*/
    if(is_empty(f->get_queue) == 1){
      wait(set);
      fenqueue(f->set_queue,pid);
      signal(set);
      suspend(pid);
      f->value = value;
      restore(mask);
      return OK;
    }
    else{
      wait(set);
      pid = fdequeue(f->get_queue);
      signal(set);
      resume(pid);
      restore(mask);
      return OK;
    }
  }

  else{   
    restore(mask);
    return SYSERR;
  }
}

syscall future_free(future_t* f){

  char *blkaddr = (char *) f;
  freemem(blkaddr, (uint32)sizeof(f));
  return OK;
}

