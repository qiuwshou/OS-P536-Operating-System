#include <xinu.h>
struct mutex_t;

syscall	mutex_create(
	struct  mutex_t  *lock
	)
{
  intmask mask = disable();
  lock->count = 0;
  restore(mask);
}
