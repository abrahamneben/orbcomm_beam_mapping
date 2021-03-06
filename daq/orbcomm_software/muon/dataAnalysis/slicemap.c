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
int plot_map(void);
int write_map(void);
int read_map(void);
int read_data(void);
int read_pass_file(void);
int test_data(void);
int plot_voltage_at_elevation(void);

//Variable Declarations

FILE *fp;
FILE *fpass;
FILE *fmapx;
FILE *ipass;
char *scans="includepass";
char powerfile[30];
char passfile[30];
char mapfile[30]="BeamMapGroupD";
char *prefix="pass";
char *p;
char powerfilename[30];
int Pindex;
int Ptotal;
int pg_id,pg_2;
char acq[15];
int i,jj,b;
char timemark[3];
char voltmark[20];
char satname[10];
int satnum=0;
int acqcount=0;
int numofacqs=50000;
int viewstep=3000;
// float f[129600];
float f[3240000];

float mapx[40][3601][901];
int azindex, elindex;
int sat_choice=0;
float altitude=800; //km
float elev=0;
 float fmin=1, fmax=0;
  float mapplot[720][180];




//********************************************************

int main(void)
{
  read_map();

  pg_id = cpgopen("/XSERVE");
  pg_2 = cpgopen("/XSERVE");

  sat_choice=0;
  plot_map();
  
  while ((elev <=90)&(elev>=0))
    {
      printf("\nElevation: ");
      scanf("%f", &elev);
      if ((elev <=90)&(elev>=0)) plot_voltage_at_elevation();
    }

  printf("End of Program\n");
  return 0;
}
//********************************************************
int read_map()
{
  int az_i, el_i;

  if ((fmapx=fopen(mapfile,"r"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }
  printf("\nReading map file: %s\n", mapfile);

  for (azindex=0; azindex<3600; azindex++)
    {
      for (elindex=0; elindex<900; elindex++)
	{
	  fscanf(fmapx,"%i",&az_i);
	  fscanf(fmapx,"%i",&el_i);
	  fscanf(fmapx,"%f\n",&mapx[sat_choice][az_i][el_i]);
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
  int deli, delj;
  float value;
  int counter;


  int i=0, j=0, k=0;
  float tr[6]= {0.0, 0.5, 0.0, 0.0, 0.0, 0.5};


  //  float RL[9]={-0.5, 0.004, 0.006, 0.008, 0.02, 0.04, 0.06, 0.08, 0.1};
  float RL[9]={-0.5, 0.0, 0.04, 0.08, 0.2, 0.4, 0.6, 0.8, 1.0};
  float RR[9]={0.0, 0.0, 0.0, 0.0, 0.6, 1.0, 1.0, 1.0, 1.0};
  float RG[9]={0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.6, 1.1, 1.0};
  float RB[9]={0.0, 0.3, 0.8, 1.0, 0.3, 0.0, 0.0, 0.0, 1.0};
  float bright=0.5; //0.53
  float contra=1.0; //1.0

  //map larger array into smaller array

  for (j=1; j<ny; j++)
    {
      for (i=1; i<nx; i++)
	{
	  value=0;
	  counter=0;
	  for (deli=0; deli<=5; deli++)
	    {
	      for (delj=0; delj<=5; delj++)
		{
		  value=value+mapx[sat_choice][(5*i)+deli][(5*j)+delj];		
		  if (mapx[sat_choice][(5*i)+deli][(5*j)+delj]>0)
		  {
		    counter++;
		    //		    printf("%i %f\n", counter, value/counter);
		  }
	      }
	    }
	  if (counter==0) mapplot[i][j]=value;
	  else mapplot[i][j]=value/counter;
	}
    }


 
  for (j=1; j<ny; j++)
    {
      for (i=1; i<nx; i++)
	{
	  k=(j-1)*nx + (i-1);
	  f[k]=mapplot[i][j];
	  if (f[k] <fmin) fmin = f[k];
	  if (f[k] >fmax) fmax = f[k];
	}
    }

  printf("min=%f max=%f\n", fmin, fmax);
  fmax=0.08;
  cpgslct(pg_id);
  cpgeras();
  cpgenv(0.0, 360, 0.0, 90, 1.0, -2); 
    cpglab("Azimuth", "Elevation", "Antenna Power Pattern: Sleeved Dipole  [Data: May 7-22, 2006]");
  cpgctab(RL, RR, RG, RB, 9, contra, bright);
    cpgimag(f, (float)nx, (float)ny, 1.0, (float)nx, 1.0, (float)ny,  fmin, fmax, tr);
  cpgbox("BCNST1",0.0,0,"BCNST1",0.0,0);
     return 0;
}
//********************************************************
int plot_voltage_at_elevation()
{
  int az_i, el_i;
  char textlineA[12]="Elevation: ";
  char textlineB[6]=" deg.";

  char elevC[10];
  float ppdb=0;
  az_i=0;
  // el_i=(int)elev*10;
el_i=(int)elev*2;

  printf("\nplotting ...");
  cpgslct(pg_2);
  cpgsci(3);
  cpgeras();
  cpgsvp(0.15f, 0.95f, 0.2f, 0.8f);
  cpgupdt();
  cpgsch(2.0);
  //  cpgswin(0, 360, 0.000f, 0.07f);
  cpgswin(0, 360, -50.0f, 10.0f);
  cpgbox("BC1NST",0.0,0,"BCNST",0.0,0);
  //  cpglab("Azimuth [Degrees]", "Voltage [volts]", "Antenna Measurement");
  cpglab("Azimuth [Degrees]", "Rel Power [dB]", "Antenna Measurement");
  //  cpgmove((float)az_i/10, mapx[sat_choice][az_i][el_i]);

  //  for (az_i=1; az_i<=3600; az_i++)
  //	 {
  //	   cpgpt1((float)az_i/10, mapx[sat_choice][az_i][el_i],-1);
  //	 }


  //for (az_i=0; az_i<=3600; az_i++)
  //	 {
  //	   ppdb=20*log(mapx[sat_choice][az_i][el_i]/0.045);
  //	   cpgpt1((float)az_i/10, ppdb, -2);
  //	 }

for (az_i=0; az_i<=720; az_i++)
	 {
	   ppdb=20*log(mapplot[az_i][el_i]/0.045);
	   cpgpt1((float)az_i/2, ppdb, -2);
	 }

  sprintf(elevC,"%i",(int)elev);
  strcat(textlineA,elevC);
  strcat(textlineA,textlineB);
  cpgtext (200,0.0, textlineA);
  return 0;
}
