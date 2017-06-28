/* lflseek.c - lflseek */

#include <xinu.h>

/*------------------------------------------------------------------------
 * lflseek  -  Seek to a specified position in a file
 *------------------------------------------------------------------------
 */
devcall	lflseek (
	  struct dentry *devptr,	/* Entry in device switch table */
	  uint32	offset		/* Byte position in the file	*/
	)
{
	struct	lflcblk	*lfptr;		/* Ptr to open file table entry	*/

	//check if the operation is valid
        pid32 pid = getpid();
	struct dentry *console = (struct dentry*) &devtab[0];
 
        if(devptr == console){
	  printf("pid of offending proc:%d\n", pid);
	}
	else{
	/* If file is not open, return an error */



	lfptr = &lfltab[devptr->dvminor];
	wait(lfptr->lfmutex);
	if (lfptr->lfstate != LF_USED) {
		signal(lfptr->lfmutex);
		return SYSERR;
	}

	/* Verify offset is within current file size */

	if (offset > lfptr->lfdirptr->ld_size) {
		signal(lfptr->lfmutex);
		return SYSERR;
	}

	/* Record new offset and invalidate byte pointer (i.e., force	*/
	/*   the index and data blocks to be replaced if a successive	*/
	/*   call is made to read or write)				*/

	lfptr->lfpos = offset;
	lfptr->lfbyte = &lfptr->lfdblock[LF_BLKSIZ];

	signal(lfptr->lfmutex);
	return OK;}
}
