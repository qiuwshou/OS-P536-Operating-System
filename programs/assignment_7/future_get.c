#include <xinu.h>
#include <future.h>




syscall future_get(future_t* f, int* value){
  pid32 pid = getpid();
  if(f->mode == FUTURE_EXCLUSIVE){
    if(f->state == FUTURE_EMPTY){//value not set yet
      f->state = FUTURE_WAITING;
      f->pid = pid;
      suspend(pid);
    }
    else if(f->state == FUTURE_READY){
      
      resume(f->pid);
      f->state = FUTURE_EMPTY;
    }
    return OK;
  }


  else if(f->mode == FUTURE_SHARED){
    if(f->state == FUTURE_EMPTY){//value not set yet
      f->state = FUTURE_WAITING;
      fenqueue(f->get_queue,pid);
      f->pid = pid;
      suspend(pid);
    }
    else if(f->state == FUTURE_WAITING){//some threads waiting for the value
      fenqueue(f->get_queue, pid);
      suspend(pid);
    }
    else{//value is set already
      while(is_empty(f->get_queue) == 0){ //while get_queue is not empty

	resume(fdequeue(f->get_queue));
      }
      future_free(f);
    }
    return OK;
  }



  else if(f->mode == FUTURE_QUEUE){
    if(f->state == FUTURE_EMPTY){//value not set yet
      fenqueue(f->get_queue,pid);
      f->state = FUTURE_WAITING;
      if(is_empty(f->set_queue) == 0){//check if set queue empty
	f->pid = fdequeue(f->set_queue);       
	resume(f->pid);
      }
      suspend(pid);
    }
    else if(f->state == FUTURE_WAITING){
      fenqueue(f->get_queue,pid);
      suspend(pid);
    }
    else{//value already set
      f->pid = fdequeue(f->set_queue);
      if(is_empty(f->get_queue) == 1){
	f->state = FUTURE_EMPTY;
      }
      else{
	resume(f->pid);
      }
    }

    return OK;
  }

  else{
    return SYSERR;
  }


}
