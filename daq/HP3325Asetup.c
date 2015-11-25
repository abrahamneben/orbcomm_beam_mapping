// HP3325Acontrol.c
// This module controls the HP3325A Synthesizer/Function Generator
// 
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "ni488.h"


#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)
#define MASK 15;

// Function Prototypes


////////////////////////////////////////////////////////////////////////
// Start of Main
int main()
{
  int sg;
  char FreqCom[11], FreqC[7], Amplitude[10], AmpC[4];
char rd[12];
 
  sg = ibdev (0, 0x11, 0x0, 0, 0, 0); //ADDR=17

  strcpy(FreqC, "4000");
  strcpy(FreqCom, "FR");
  strcat(FreqCom,FreqC);
  strcat(FreqCom,"KH");
  ibwrt (sg, FreqCom, 8);

  strcpy(AmpC, "2.0");
  strcpy(Amplitude, "AM");
  strcat(Amplitude,AmpC);
  strcat(Amplitude,"VO");
  ibwrt (sg, Amplitude, 7);

ibwrt(sg,"IFR",3);
 ibrd(sg,rd,12);
printf("%s\n",rd);
  return 0;
}
// End of Main
