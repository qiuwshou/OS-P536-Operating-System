//funcion defines
#include <xinu.h>
#include <delay.h>
#include <stdlib.h>
#include <stdio.h>
void rand_delay(int uS_max){
  int r = rand() % uS_max + 1;
  sleepms(r);   
}
