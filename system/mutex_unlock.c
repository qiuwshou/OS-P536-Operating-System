#include <xinu.h>


syscall mutex_unlock(struct mutex_t* lock){
  intmask mask = disable();
  lock->count = 0;
  restore(mask);
}
