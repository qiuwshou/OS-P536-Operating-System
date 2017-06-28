#include <xinu.h>
#include <a6.h>

syscall tsa(struct mutex_t* lock){
  intmask mask = disable();
  int32 temp = &lock->count;
  lock->count = 1;
  restore(mask);
  return  temp;
}
