#include <xinu.h>
//#include <a6.h>

syscall cond_init(struct cond_t* cv){
  cv->cond = 0; //1 need to fill, 0 ready to eat
  mutex_create(&cv->mx);
}
