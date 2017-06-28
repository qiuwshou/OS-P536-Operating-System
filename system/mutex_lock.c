#include <xinu.h>


syscall mutex_lock(struct mutex_t* lock){

  while(tsa(lock) == 1);

}
