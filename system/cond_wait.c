#include <xinu.h>


syscall cond_wait(struct cond_t *cv, struct mutex_t *lock){
  
  //mutex_unlock(lock);
  mutex_lock(&cv->mx);
  cv->cond = 1;
  mutex_unlock(&cv->mx);  
  mutex_unlock(lock);
  mutex_lock(lock);
}
