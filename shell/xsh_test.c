#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

shellcmd xsh_test(int nargs, char *args[]) {

  //seek on console

  struct dentry *console;
  struct dentry *lf0;

  intmask mask = disable();

  console = (struct dentry *)&devtab[0];
  lf0 = (struct dentry *)&devtab[5];

  (*lf0->dvseek)(console,0);
  
  restore(mask);

  return 0;
}
