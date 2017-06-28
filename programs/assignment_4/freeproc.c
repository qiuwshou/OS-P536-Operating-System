/* freeproc.c - freeproc */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  freeproc - free the dying process
 *------------------------------------------------------------------------
 */
void freeproc()
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr; 
	pid32 pid;
	int32 i;

	mask = disable();               /* Check if the protab is valid */
	if ((pid32)(sizeof(&proctab)) >= NPROC) {
		restore(mask);
		return SYSERR;
	}

        for(i=0; i<NPROC; i++){
	  prptr = &proctab[i];
	  if(prptr->prstate == PR_DYING){
	    freestk(prptr->prstkbase, prptr->prstklen);
	    prptr->prstate = PR_FREE;
	    resched();
	  }
	}

	restore(mask);
        return OK;
}
