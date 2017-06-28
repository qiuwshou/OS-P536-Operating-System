#include <xinu.h>
#include <future.h>

syscall future_free(future_t* f){
  
  char *blkaddr = (char *) f;
  freemem(blkaddr, (uint32)sizeof(f));  
  
}
