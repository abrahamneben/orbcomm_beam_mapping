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
  float bin1[520];
  float bin2[520];
} acqdata[50001];

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
int satsearch(void);
int plot_freq_data(float signal[5000]);
int plot_freq_data2(float signal2[5000]);

//Variable Declarations

FILE *fp;
FILE *fpout;
FILE *ffav;
char *powerfile="/data/satpower20060924.0";
char *favfile="favorites";
int pg_id, pg_id2;
char acq[15];
char fm[10];
int i,jj,b;
char timemark[5];
char voltmark[20];
char chanmark[20];
char satname[10];
int satnum=0;
int acqcount=0;
int numofacqs=50000;
int viewstep=3000;
float f[15000000];
int numoffav;
float flo=139.000;
int favsat, favbin;
int counter, start, stop;

char passfile[30];
char p[2];

//********************************************************

int main(void)
{
  pg_id = cpgopen("/XSERVE");
  cpgpap(5.0, 0.8);
  cpgask(0);
  if ((fp=fopen(powerfile,"r"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }

  pg_id2 = cpgopen("/XSERVE");
  cpgpap(5.0, 0.8);
  cpgask(0);
 
  if ((ffav=fopen(favfile,"r"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }
  fscanf(ffav, "%d", &numoffav);

  printf("\nReading data file ...\n");
  for (acqcount=1; acqcount < (numofacqs+1); acqcount++) read_data();
  satsearch();
  //  printf("Plotting ...\n");
  //  plot_data();
       int fclose(FILE *fp);
       int fclose(FILE *ffav);

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
     fscanf(fp,"%s%s",fm,satname);
     //     printf("%s %s\n", fm, satname);
     if (strcmp(satname, "1")==0)
       {
	 satnum=1;
	 fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	 acqdata[i].Sat[satnum].ALH=1;
       }
     else if (strcmp(satname, "2")==0)
	{
	  satnum=2;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "3")==0)
	{
	  satnum=3;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "4")==0)
	{
	  satnum=4;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "5")==0)
	{
	  satnum=5;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "6")==0)
	{
	  satnum=6;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "7")==0)
	{
	  satnum=7;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "8")==0)
	{
	  satnum=8;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "9")==0)
	{
	  satnum=9;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "10")==0)
	{
	  satnum=10;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "11")==0)
	{
	  satnum=11;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "12")==0)
	{
	  satnum=12;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "13")==0)
	{
	  satnum=13;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "14")==0)
	{
	  satnum=14;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "15")==0)
	{
	  satnum=15;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "16")==0)
	{
	  satnum=16;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "17")==0)
	{
	  satnum=17;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "18")==0)
	{
	  satnum=18;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "19")==0)
	{
	  satnum=19;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "20")==0)
	{
	  satnum=20;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "21")==0)
	{
	  satnum=21;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "22")==0)
	{
	  satnum=22;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "23")==0)
	{
	  satnum=23;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "24")==0)
	{
	  satnum=24;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "25")==0)
	{
	  satnum=25;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "26")==0)
	{
	  satnum=26;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "27")==0)
	{
	  satnum=27;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "28")==0)
	{
	  satnum=28;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "29")==0)
	{
	  satnum=29;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "30")==0)
	{
	  satnum=30;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "31")==0)
	{
	  satnum=31;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "32")==0)
	{
	  satnum=32;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "33")==0)
	{
	  satnum=33;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "34")==0)
	{
	  satnum=34;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "35")==0)
	{
	  satnum=35;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
	else if (strcmp(satname, "36")==0)
	{
	  satnum=36;
	  fscanf(fp,"%f%f%f", &acqdata[i].Sat[satnum].az, &acqdata[i].Sat[satnum].el, &acqdata[i].Sat[satnum].range);
	  acqdata[i].Sat[satnum].ALH=1;
	}
   }  
 while (strcmp(fm, "Bin")!=0);
 // printf("%s %d \n%s %s %s %s %s %s\n", acq, i, timemark, acqdata[i].UT.wkday, acqdata[i].UT.month,acqdata[i].UT.dateX, acqdata[i].UT.utime, acqdata[i].UT.year);
 //for (jj=1; jj<37; jj++)
 // {
 //    printf("%d %f %f %f %d\n", jj, acqdata[i].Sat[jj].az, acqdata[i].Sat[jj].el, acqdata[i].Sat[jj].range, acqdata[i].Sat[jj].ALH);
 //  }
 fscanf(fp, "%s", chanmark);
 fscanf(fp, "%s", chanmark);
 fscanf(fp, "%s", chanmark);
 fscanf(fp, "%s", chanmark);

 for (b=1; b<513; b++)
   {
     fscanf(fp, "%f%f", &acqdata[i].bin1[b], &acqdata[i].bin2[b]);
   }
 // for (b=1; b<513; b++)
 //  {
 //    printf("%d %f  %f \n", b, acqdata[i].bin1[b], acqdata[i].bin2[b]);
 //   }
      return 0;
}
//********************************************************
int satsearch()
{
  float favsatfreq;
  int z, jj, mm; 
  float power1[5000], power2[5000];
  int special=375;
  char time[8];
  float rawp1,rawp2;
  char ch, ansr='y';
  
  for (jj=1; jj<=numoffav; jj++)
    {
            fscanf(ffav, "%d", &favsat);
            fscanf(ffav, "%f", &favsatfreq);
	    start=0;
            stop=0;
	    counter=0;
            sprintf(time,"%s", ""); 
	    sprintf(passfile,"%s", "FM"); 
            ch=0;

      favbin= (int) rint((flo-favsatfreq)/0.004);
      z=1;
      while (z<numofacqs)
	{
 	   if (counter <1) printf("Searching for satellite FM %d ...", favsat);
	   if (counter >=1) 
	     {
	       printf("Continue searching for satellite FM %d ...", favsat);
	       sprintf(passfile,"%s", "FM"); 
	     }
	   while (acqdata[z].Sat[favsat].ALH==0)
	    {
	      if(z==numofacqs) 
		{
		  printf("none found.\n");
		  break;
		}
	      else z++;
	    }
	  counter=1;
	  start=z;
	  while (acqdata[z].Sat[favsat].ALH==1)
	    {
	      if (counter==1)
		{
		printf("Found!\n");
		printf("     Using frequency bin %d\n", favbin); 
		printf("     Start: %d    ", start);
		printf("%s %s %s %s %s UT\n", acqdata[z].UT.wkday, acqdata[z].UT.month, acqdata[z].UT.dateX, acqdata[z].UT.utime, acqdata[z].UT.year);
		}
	      power1[counter]= acqdata[z].bin1[favbin-3]+acqdata[z].bin1[favbin-2]+acqdata[z].bin1[favbin-1]+acqdata[z].bin1[favbin]+acqdata[z].bin1[favbin+1]+acqdata[z].bin1[favbin+2]+acqdata[z].bin1[favbin+3];
	      power2[counter]= acqdata[z].bin2[special-2]+acqdata[z].bin2[special-1]+acqdata[z].bin2[special]+acqdata[z].bin2[special+1]+acqdata[z].bin2[special+2];
	      //	      printf("Power1 = %f   Power2 = %f\n",power1[counter],power2[counter]);
	      counter++;
	      z++;
	    }
	  stop=start+counter-1;
	  
	  if (counter>1) printf("     Stop: %d\n", stop);
	  if (counter>1) 
	    {
	      plot_freq_data(power1);
	      plot_freq_data2(power2);
	      //
	      ch=getch();
	      if (ch==ansr)
		{
		  sprintf(p,"%d", favsat); 
		  strcat(passfile,p);
		  strcat(passfile,acqdata[start].UT.month);
		  strcat(passfile,acqdata[start].UT.dateX);
		  strcat(passfile,"h");	      
		  strncpy(time, acqdata[start].UT.utime, 8);
		  strncat(passfile,time,2);
		  strcat(passfile,"y");
		  strcat(passfile,acqdata[start].UT.year);
		  printf("Storing in File: %s\n\n",passfile);

		  if ((fpout=fopen(passfile,"w"))==NULL)
		    {
		  printf("Cannot open file. \n");
		  exit(1);
		    }
		  fprintf(fpout,"%u %d\n",counter-1, favbin);		  
		  fprintf(fpout, "%s %s %s %s %s UT\n", acqdata[start].UT.wkday, acqdata[start].UT.month, acqdata[start].UT.dateX, acqdata[start].UT.utime, acqdata[start].UT.year);
		  fprintf(fpout,"Azimuth     Elevation    Range       RawV1      RawV2\n" );
		  for (mm=start; mm<stop; mm++)
		    {
		      rawp1=acqdata[mm].bin1[favbin-3]+acqdata[mm].bin1[favbin-2]+acqdata[mm].bin1[favbin-1]+acqdata[mm].bin1[favbin]+acqdata[mm].bin1[favbin+1]+acqdata[mm].bin1[favbin+2]+acqdata[mm].bin1[favbin+3];
		      rawp2=acqdata[mm].bin2[special-3]+acqdata[mm].bin2[special-2]+acqdata[mm].bin2[special-1]+acqdata[mm].bin2[special]+acqdata[mm].bin2[special+1]+acqdata[mm].bin2[special+2]+acqdata[mm].bin2[special+3];
		      fprintf(fpout,"%f  %f  %f  %f  %f\n", acqdata[mm].Sat[favsat].az, acqdata[mm].Sat[favsat].el, acqdata[mm].Sat[favsat].range, rawp1,rawp2); 
		    }
		  int fclose(FILE *fpout);
		}
 	    }
	}
    }
	
  //  printf("Sat Number: %d\nRF Freq:  %f\nBin Number:  %d\n", favsat, favsatfreq, favbin);

  return(0);
}

//********************************************************
int plot_freq_data(float signal[5000])
{
  int acquisition=0, data=0;;
  cpgslct(pg_id);
  cpgeras();
  cpgswin(1, counter, 0.0f, 0.08f);
  cpgbox("BC1NST",0.0,0,"BCNST",0.0,0);
  cpglab("Relative acquisition number", "RMS Voltage Amplitude [volts]", "Antenna Measurement Receiver - CH 1");
  cpgmove(data, signal[0]);
  for (acquisition=1; acquisition<=counter; acquisition++)
	 {
	   cpgdraw(acquisition, signal[acquisition]);
	 }
  return 0;
}


int plot_freq_data2(float signal2[5000])
{
  int acquisition=0, data=0;
  cpgslct(pg_id2);
  cpgeras();
  cpgswin(1, counter, 0.0f, 0.01f);
  cpgbox("BC1NST",0.0,0,"BCNST",0.0,0);
  cpglab("Relative acquisition number", "RMS Voltage Amplitude [volts]", "Antenna Measurement Receiver - CH 2");
  cpgmove(data, signal2[0]);
  for (acquisition=1; acquisition<=counter; acquisition++)
	 {
	   cpgdraw(acquisition, signal2[acquisition]);
	 }
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
	  f[k]=acqdata[i].bin1[j];
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
			  Power=acqdata[x1].bin1[y1];    
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
