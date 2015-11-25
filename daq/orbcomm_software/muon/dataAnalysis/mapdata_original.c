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

//Variable Declarations

FILE *fp;
FILE *fpout;
FILE *fmap;
FILE *fmapx;
char *powerfile="satpower20060219.2c";
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
  pg_id = cpgopen("/XSERVE");
  cpgpap(14.0, 0.7);
  cpgask(0);
  zero_map();
  write_map();
  read_map();
  plot_map();
  int fclose(FILE *fmap);
  int fclose(FILE *fmapx);
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
map[360][90]=1;
map[263][125]=0.8;
map[32][12]=0.6;
map[171][111]=0.8;
map[95][55]=1;
map[600][160]=1;

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
int read_map()
{
  if ((fmapx=fopen(mapfile,"r"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }

  for (azindex=0; azindex<720; azindex++)
    {
      for (elindex=0; elindex<180; elindex++)
	{
	  fscanf(fmapx,"%f",&mapx[azindex][elindex]);
	}
    }
  printf("Map file: %s read.\n", mapfile);
  return 0;
}

//********************************************************
int plot_map()
{
  int nx=720;
  int ny=180;

  int i=0, j=0, k=0;
  float tr[6]= {0.0, 0.5, 0.0, 0.0, 0.0, 0.5};
  int x=0, y=0;

  float fmin=1, fmax=0;
   float RL[9]={-0.5, 0.0, 0.17, 0.33, 0.50, 0.67, 0.83, 1.0, 1.7};
  float RR[9]={0.0, 0.0, 0.0, 0.0, 0.6, 1.0, 1.0, 1.0, 1.0};
  float RG[9]={0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.6, 1.1, 1.0};
  float RB[9]={0.0, 0.3, 0.8, 1.0, 0.3, 0.0, 0.0, 0.0, 1.0};
  float bright=0.53; //0.53
  float contra=1.0; //1.0
 
  for (j=1; j<ny; j++)
    {
      for (i=1; i<nx; i++)
	{
	  k=(j-1)*nx + (i-1);
	  x=tr[0]+tr[1]*i+tr[2]*j;
	  y=tr[3]+tr[4]*i+tr[5]*j;
	  f[k]=mapx[i][j];
	  if (f[k] <fmin) fmin = f[k];
	  if (f[k] >fmax) fmax = f[k];
	}
    }

  printf("min=%f max=%f\n", fmin, fmax);
  fmax=fmax/10;
  cpgslct(pg_id);
  cpgctab(RL, RR, RG, RB, 9, contra, bright);
     cpgenv((float)0.0, (float)nx*tr[1], 0.0, (float)ny*tr[5], 1.0, -2); 
    cpgbox("BCNST1",0.0,0,"BCNST1",0.0,0);
    cpglab("Azimuth", "Elevation", "Antenna Power Pattern");
    cpgimag(f, nx, ny, 1.0, nx, 1.0, ny,  fmin, fmax, tr);

     return 0;
}
