#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>
#include <arpa/inet.h>
#include "dask.h"
#include "conio.h"
#include "cpgplot.h"
#include <fftw3.h>

#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)

struct Acquisition
{
  struct
  {
    char wkday[128];
    char month[128];
    char dateX[128];
    char utime[128];
    char year[128];
  } UT;

  struct Satellite
  {
    int ALH;
    float az;
    float el;
    float range;
  } Sat[40];
  float bin[260];
} acqdata[51000];

struct PassInfo
{
  int sat_id;
  int start_acq;
  int stop_acq;
  int peak_bin;
} pass[25];

//prototypes
int zero_map(void);
int plot_map(void);
int write_map(void);
int read_map(void);
int read_data(void);

//Variable Declarations

FILE *fp;
FILE *fpout;
FILE *fmap;
FILE *fmapx;
char *powerfile="satpower20060507.0c";
char passfile[30]="pass";
char mapfile[30]="BeamMap01";
char *p;
int pg_id;
char acq[15];
int i,jj,b;
char timemark[3];
char voltmark[20];
char satname[10];
int satnum=0;
int acqcount=0;
int numofacqs=50000;
int viewstep=3000;
float f[15000000];

float map[720][180];
float mapx[720][180];
int azindex, elindex;

//********************************************************

int main(void)
{
  zero_map();
  write_map();
  printf("End of Program\n");
  return 0;
}
//********************************************************
int zero_map()
{

  for (azindex=0; azindex<720; azindex++)
    {
      for (elindex=0; elindex<180; elindex++)
	{
	  map[azindex][elindex]=0;
	  mapx[azindex][elindex]=0;
	}
    }
 return 0;
}


//********************************************************
int write_map()
{
  if ((fmap=fopen(mapfile,"w"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }

  for (azindex=0; azindex<720; azindex++)
    {
      for (elindex=0; elindex<180; elindex++)
	{
	  fprintf(fmap,"%f\n",map[azindex][elindex]);
	}
    }
  printf("Map file: %s saved.\n", mapfile);
  return 0;
}

//********************************************************

