#include <xinu.h>


syscall cond_signal(struct cond_t* cv){
  mutex_lock(&cv->mx);
  intmask mask = disable();
  cv->cond = 0;
  restore(mask);
  mutex_unlock(&cv->mx);
}
