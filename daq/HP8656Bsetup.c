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
  char FreqCom[11], FreqC[7], Amplitude[10], AmpC[4], Modulation[4];
char rd[12];
 
  sg = ibdev (0, 0x15, 0x0, 0, 0, 0); //ADDR=21

  strcpy(FreqC, "127000");
  strcpy(FreqCom, "FR");
  strcat(FreqCom,FreqC);
  strcat(FreqCom,"KZ");
  ibwrt (sg, FreqCom, 10);

  strcpy(AmpC, "+10");
  strcpy(Amplitude, "AP");
  strcat(Amplitude,AmpC);
  strcat(Amplitude,"DM");
  ibwrt (sg, Amplitude, 7);

  strcpy(Modulation, "AM");
  strcat(Modulation,"S4");
  ibwrt (sg, Modulation, 4);

//ibwrt(sg,"IFR",3);
//ibrd(sg,rd,12);
//printf("%s\n",rd);
  return 0;
}
// End of Main
