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
int read_data(void);
int plot_data(void);

//Variable Declarations

FILE *fp;
FILE *fpout;
char *powerfile="satpower20060522.9c";
char passfile[30]="pass";;
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
//********************************************************

int main(void)
{
  pg_id = cpgopen("/XSERVE");
  cpgpap(14.0, 0.7);
  cpgask(0);
  if ((fp=fopen(powerfile,"r"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }

  p=strpbrk(powerfile,"2");
  strcat(passfile,p);
  //  printf("%s\n",passfile);

  if ((fpout=fopen(passfile,"w"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }


  printf("\nReading data file ...\n");
  for (acqcount=1; acqcount < (numofacqs+1); acqcount++) read_data();
  printf("Plotting ...\n");
  plot_data();
       int fclose(FILE *fp);
      printf("End of Program\n");
  return 0;
}
//********************************************************
int read_data()
{

  fscanf(fp,"%s%d", acq, &i);
  fscanf(fp,"%s%s%s%s%s%s", timemark, acqdata[i].UT.wkday, acqdata[i].UT.month, acqdata[i].UT.dateX, acqdata[i].UT.utime, acqdata[i].UT.year);
 do
   {
     fscanf(fp,"%s",satname);
     if (strcmp(satname, "A1(FM05)")==0)
       {
	  satnum=1;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
       }
     else if (strcmp(satname, "A2(FM06)")==0)
	{
	  satnum=2;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "A3(FM07)")==0)
	{
	  satnum=3;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "A4(FM08)")==0)
	{
	  satnum=4;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "A5(FM09)")==0)
	{
	  satnum=5;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "A6(FM10)")==0)
	{
	  satnum=6;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "A7(FM11)")==0)
	{
	  satnum=7;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "A8(FM12)")==0)
	{
	  satnum=8;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "B1(FM13)")==0)
	{
	  satnum=9;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "B2(FM14)")==0)
	{
	  satnum=10;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "B3(FM15)")==0)
	{
	  satnum=11;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "B4(FM16)")==0)
	{
	  satnum=12;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "B5(FM17)")==0)
	{
	  satnum=13;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "B6(FM18)")==0)
	{
	  satnum=14;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "B7(FM19)")==0)
	{
	  satnum=15;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "B8(FM20)")==0)
	{
	  satnum=16;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "C1(FM21)")==0)
	{
	  satnum=17;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "C2(FM22)")==0)
	{
	  satnum=18;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "C3(FM23)")==0)
	{
	  satnum=19;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "C4(FM24)")==0)
	{
	  satnum=20;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "C5(FM25)")==0)
	{
	  satnum=21;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "C6(FM26)")==0)
	{
	  satnum=22;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "C7(FM27)")==0)
	{
	  satnum=23;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "C8(FM28)")==0)
	{
	  satnum=24;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "D1(FM29)")==0)
	{
	  satnum=25;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "D2(FM30)")==0)
	{
	  satnum=26;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "D3(FM31)")==0)
	{
	  satnum=27;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "D4(FM32)")==0)
	{
	  satnum=28;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "D5(FM33)")==0)
	{
	  satnum=29;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "D6(FM34)")==0)
	{
	  satnum=30;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "D7(FM35)")==0)
	{
	  satnum=31;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "D8(FM36)")==0)
	{
	  satnum=32;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "F2(FM02)")==0)
	{
	  satnum=33;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "G2(FM04)")==0)
	{
	  satnum=34;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
   }  
 while (strcmp(satname, "Bin")!=0);
 //printf("%s %d \n %s %s %s %s %s %s\n",acq,i,timemark, acqdata[i].UT.wkday, acqdata[i].UT.month,acqdata[i].UT.dateX, acqdata[i].UT.utime, acqdata[i].UT.year);
 //for (jj=1; jj<35; jj++)
 //  {
 //    printf("%d %f %f %f %d\n", jj, acqdata[i].Sat[jj].az, acqdata[i].Sat[jj].el, acqdata[i].Sat[jj].range, acqdata[i].Sat[jj].ALH);
 //  }
 fscanf(fp, "%s", voltmark);
 for (b=1; b<257; b++)
   {
     fscanf(fp, "%f", &acqdata[i].bin[b]);
   }
 // for (b=1; b<257; b++)
 //    {
 //      printf("%d %f \n", b, acqdata[i].bin[b]);
 //    }
      return 0;
}
//********************************************************
int plot_data()
{
  int xstart=1;
  int xstop=9000;

  int nx=50000;
  int ny=300;

  int i=0, j=0, k=0, m=0;
  float tr[6]= {0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  int x=0, y=0, x1=0, y1=0;

  float xc=0, yc=0, xcc=0, ycc=0;
  int xic=0, xicc=0, yic=0, yicc=0;
  char w;
  float fmin=1, fmax=0;
  float Pmax=0;
  float Power=0;
  float RL[9]={-0.5, 0.0, 0.17, 0.33, 0.50, 0.67, 0.83, 1.0, 1.7};
  float RR[9]={0.0, 0.0, 0.0, 0.0, 0.6, 1.0, 1.0, 1.0, 1.0};
  float RG[9]={0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.6, 1.1, 1.0};
  float RB[9]={0.0, 0.3, 0.8, 1.0, 0.3, 0.0, 0.0, 0.0, 1.0};
  float bright=0.53; //0.53
  float contra=1.0; //1.0
  int loop;
  int satcount=0;

  for (j=1; j<=250; j++)
    {
      for (i=1; i<=nx; i++)
	{
	  k=(j-1)*nx + (i-1);
	  x=tr[0]+tr[1]*i+tr[2]*j;
	  y=tr[3]+tr[4]*i+tr[5]*j;
	  f[k]=acqdata[i].bin[j];
	  if (f[k] <fmin) fmin = f[k];
	  if (f[k] >fmax) fmax = f[k];
	}
    }

 for (j=261; j<=300; j++)
    {
      for (i=1; i<=nx; i++)
	{
	  k=(j-1)*nx + (i-1);
	  x=tr[0]+tr[1]*i+tr[2]*j;
	  y=tr[3]+tr[4]*i+tr[5]*j;
	  f[k]=acqdata[i].Sat[j-260].ALH;
	}
    }


  printf("min=%f max=%f\n", fmin, fmax);
  fmax=fmax/10;
  cpgslct(pg_id);
  cpgctab(RL, RR, RG, RB, 9, contra, bright);
  //cpgsvp(0.07f, 0.95f, 0.05f, 0.95f);
  //cpgwnad((float)1.0, (float)nx, 0.0, (float)ny);

  for (loop=1; loop<15; loop++)
    {
    cpgenv((float)xstart, (float)xstop, 1.0, (float)ny, 12.0, -2); 
    cpgbox("BCNST1",0.0,0,"BCNST1",0.0,0);
    cpglab("Acquisition Number", "Frequency Bins", "Antenna Measurement Receiver");
    cpgimag(f, nx, ny, xstart, xstop, 1.0, ny,  fmin, fmax, tr);
    cpgcurs(&xc, &yc, &w);
    cpgband(2,0,xc,yc,&xcc,&ycc,&w);
       while((yc > 0)&&(ycc>0))
	{
	  xic=(int)xc;
	  xicc=(int)xcc;
	  yic=(int)yc;
	  yicc=(int)ycc;
	  for (m=1; m<40; m++)
	    {
	      if ((acqdata[xic].Sat[m].ALH == 1)&&(acqdata[xicc].Sat[m].ALH == 1))
		{
		  satcount++;
		  printf("%f %f\n",xc, yc);
		  printf("%f %f\n",xcc, ycc);
		  //		  printf("Satellite is # %d\n\n", m);
		  pass[satcount].sat_id=m;
		  while(acqdata[xic].Sat[m].ALH == 1)
		    {
		      pass[satcount].start_acq=xic;
		      xic--;
		    }
		  while(acqdata[xicc].Sat[m].ALH == 1)
		    {
		      pass[satcount].stop_acq=xicc;
		      xicc++;
		    }
		  for (x1=xic; x1<=xicc; x1++)
		    {
		      for(y1=yic; y1<=yicc; y1++)
			{
			  Power=acqdata[x1].bin[y1];    
			  if ( Power >= Pmax)
			    {
			      Pmax = Power;
			      pass[satcount].peak_bin = y1;
			    }
			}
		    }
		  printf("Satellite: %d\n", pass[satcount].sat_id);
		  printf("  Start Acq: %d\n", pass[satcount].start_acq);
		  printf("  Stop Acq: %d\n", pass[satcount].stop_acq);
		  printf("  Peak Bin: %d\n", pass[satcount].peak_bin);
		  printf("  Maximum Power:  %f\n\n",Pmax);
		  fprintf(fpout, "%i %i %i %i\n", pass[satcount].sat_id, pass[satcount].start_acq, pass[satcount].stop_acq, pass[satcount].peak_bin);

		}
	      Power=0; Pmax=0; x1=0; y1=0;
	    }
	  cpgcurs(&xc, &yc, &w);
	  cpgband(2,0,xc,yc,&xcc,&ycc,&w);
	}
      xstart=xstart+viewstep;
      xstop=xstop+viewstep;
    }
     return 0;
}
