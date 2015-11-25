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
int group_data(void);

//Variable Declarations

FILE *fp;
FILE *fpass;
FILE *fmapx;
FILE *fmapxA;
FILE *fmapxB;
FILE *fmapxC;
FILE *fmapxD;
FILE *ipass;
char *scans="includepass";
char powerfile[30];
char passfile[30];
char mapfile[30]="BeamMapALL";
char mapfileA[30]="BeamMapGroupA";
char mapfileB[30]="BeamMapGroupB";
char mapfileC[30]="BeamMapGroupC";
char mapfileD[30]="BeamMapGroupD";
char *prefix="pass";
char *p;
char powerfilename[30];
int Pindex;
int Ptotal;
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
// float f[129600];
float f[3240000];

float mapx[40][3601][901];
int azindex, elindex;
int sat_choice=0;
float altitude=800; //km



//********************************************************

int main(void)
{
  if ((ipass=fopen(scans,"r"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }
  fscanf(ipass,"%i", &Ptotal);
 
   for (Pindex=1; Pindex<=Ptotal; Pindex++)
    {
      fscanf(ipass,"%s", powerfile);
      //      printf("%s\n",powerfile);
      if ((fp=fopen(powerfile,"r"))==NULL)
	{
      	  printf("Cannot open file. \n");
	  exit(1);
	}
      strcpy(passfile,"");
      strcat(passfile,prefix);
      p=strpbrk(powerfile,"2");
      strcat(passfile,p);
      //     printf("%s\n",passfile);
  if ((fpass=fopen(passfile,"r"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }
  printf("\nReading data file %s \n",powerfile);

  for (acqcount=1; acqcount < (numofacqs+1); acqcount++) read_data();
  read_pass_file();
  //  test_data();
  fclose(fpass);
  fclose(fp);
    }
  group_data();
  pg_id = cpgopen("/XSERVE");

  while (sat_choice <100)
    {
      printf("\nPlot Satellite: ");
      scanf("%i", &sat_choice);
      if (sat_choice<40) plot_map();
    }
      
  write_map();
  fclose(ipass);
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
 fscanf(fp, "%s", voltmark);
 for (b=1; b<257; b++)
   {
     fscanf(fp, "%f", &acqdata[i].bin[b]);
   }
      return 0;
}
//********************************************************
int write_map()
{
  if ((fmapx=fopen(mapfile,"w"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }

  if ((fmapxA=fopen(mapfileA,"w"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }

  if ((fmapxB=fopen(mapfileB,"w"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }

  if ((fmapxC=fopen(mapfileC,"w"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }

  if ((fmapxD=fopen(mapfileD,"w"))==NULL)
    {
      printf("Cannot open file. \n");
      exit(1);
    }

  printf("\nWriting Map file %s...\n", mapfile);
  for (azindex=0; azindex<3600; azindex++)
    {
      for (elindex=0; elindex<900; elindex++)
	{
	  fprintf(fmapx," %i %i %f\n", azindex, elindex, mapx[0][azindex][elindex]);
	}
    }
  printf("Map file: %s saved.\n", mapfile);

  printf("\nWriting Map file %s...\n", mapfileA);
for (azindex=0; azindex<3600; azindex++)
    {
      for (elindex=0; elindex<900; elindex++)
	{
	  fprintf(fmapxA," %i %i %f\n", azindex, elindex, mapx[36][azindex][elindex]);
	}
    }
  printf("Map file: %s saved.\n", mapfileA);

  printf("\nWriting Map file %s...\n", mapfileB);
for (azindex=0; azindex<3600; azindex++)
    {
      for (elindex=0; elindex<900; elindex++)
	{
	  fprintf(fmapxB," %i %i %f\n", azindex, elindex, mapx[37][azindex][elindex]);
	}
    }
  printf("Map file: %s saved.\n", mapfileB);

  printf("\nWriting Map file %s...\n", mapfileC);
for (azindex=0; azindex<3600; azindex++)
    {
      for (elindex=0; elindex<900; elindex++)
	{
	  fprintf(fmapxC," %i %i %f\n", azindex, elindex, mapx[38][azindex][elindex]);
	}
    }
  printf("Map file: %s saved.\n", mapfileC);

  printf("\nWriting Map file %s...\n", mapfileD);
for (azindex=0; azindex<3600; azindex++)
    {
      for (elindex=0; elindex<900; elindex++)
	{
	  fprintf(fmapxD," %i %i %f\n", azindex, elindex, mapx[39][azindex][elindex]);
	}
    }
  printf("Map file: %s saved.\n", mapfileD);
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

  for (azindex=0; azindex<360; azindex++)
    {
      for (elindex=0; elindex<90; elindex++)
	{
	  fscanf(fmapx,"%f",&mapx[0][azindex][elindex]);
	}
    }
  printf("Map file: %s read.\n", mapfile);
  return 0;
}

//********************************************************
int read_pass_file()
{
  int entries;
  int indexA=1;
  int indexB=1;
  float tpower;
  int az_i;
  int el_i;

  fscanf(fpass, "%i \n", &entries);
  printf("Number of entries: %d \n", entries);
  printf("Pass Information:\n");

  for (indexA=1; indexA<=entries; indexA++)
    {
      fscanf(fpass, "%i %i %i %i \n", &pass[indexA].sat_id, &pass[indexA].start_acq, &pass[indexA].stop_acq, &pass[indexA].peak_bin);

      //      if (pass[indexA].sat_id==sat_choice)
      //	{
	  printf("%i %i %i %i \n", pass[indexA].sat_id, pass[indexA].start_acq, pass[indexA].stop_acq, pass[indexA].peak_bin);
	  for (indexB=pass[indexA].start_acq; indexB<=pass[indexA].stop_acq; indexB++)
	    {
	      tpower=0;
	      tpower=acqdata[indexB].bin[pass[indexA].peak_bin-2]+acqdata[indexB].bin[pass[indexA].peak_bin-1]+acqdata[indexB].bin[pass[indexA].peak_bin]+acqdata[indexB].bin[pass[indexA].peak_bin+1]+acqdata[indexB].bin[pass[indexA].peak_bin+2];
	      tpower=tpower*(acqdata[indexB].Sat[pass[indexA].sat_id].range)/altitude; //correction for range

	      az_i=(int) rint(10*acqdata[indexB].Sat[pass[indexA].sat_id].az);
	       el_i=(int) rint(10*acqdata[indexB].Sat[pass[indexA].sat_id].el);

	       if (mapx[pass[indexA].sat_id][az_i][el_i]==0) mapx[pass[indexA].sat_id][az_i][el_i]= tpower;
	       //	       else mapx[pass[indexA].sat_id][az_i][el_i]= (mapx[pass[indexA].sat_id][az_i][el_i]+tpower)/2;

	       if (mapx[0][az_i][el_i]==0) mapx[0][az_i][el_i]= tpower;
	       //	       else mapx[0][az_i][el_i]= (mapx[0][az_i][el_i]+tpower)/2;
	      //	      printf("az = %f el = %f power= %f mapx= %f\n",acqdata[indexB].Sat[sat_choice].az,acqdata[indexB].Sat[sat_choice].el, tpower, mapx[indexA][az_i][el_i]);
	       //	    }
	    }
    }
  return 0;
}
//********************************************************
int group_data()
{
  int group_index=0;
  int azindex=0;
  int elindex=0;

  printf("\nGrouping satellite data by orbit plane ..");
  printf("\nGroupA: FM05-12 in 36");
  printf("\nGroupB: FM13-20 in 37");
  printf("\nGroupC: FM21-28 in 38");
  printf("\nGroupD: FM30-36 in 39");

  for (azindex=0; azindex<3600; azindex++)
    {
      for (elindex=0; elindex<900; elindex++)
	{ 
	  for (group_index=1; group_index<=8; group_index++) //Group A in 36
	    {
	      if (mapx[36][azindex][elindex]==0) mapx[36][azindex][elindex]= mapx[group_index][azindex][elindex];
	      //	      else mapx[36][azindex][elindex]=(mapx[36][azindex][elindex]+mapx[group_index][azindex][elindex])/2;	    
	    }
	  for (group_index=9; group_index<=16; group_index++) //Group A in 37
	    {
	      if (mapx[37][azindex][elindex]==0) mapx[37][azindex][elindex]= mapx[group_index][azindex][elindex];
	      //	      else mapx[37][azindex][elindex]=(mapx[37][azindex][elindex]+mapx[group_index][azindex][elindex])/2;	    
	    }
	  for (group_index=17; group_index<=24; group_index++) //Group A in 38
	    {
	      if (mapx[38][azindex][elindex]==0) mapx[38][azindex][elindex]= mapx[group_index][azindex][elindex];
	      //	      else mapx[38][azindex][elindex]=(mapx[38][azindex][elindex]+mapx[group_index][azindex][elindex])/2;	
	    }    
	  for (group_index=25; group_index<=32; group_index++) //Group A in 39
	    {
	      if (mapx[39][azindex][elindex]==0) mapx[39][azindex][elindex]= mapx[group_index][azindex][elindex];
	      //	      else mapx[39][azindex][elindex]=(mapx[39][azindex][elindex]+mapx[group_index][azindex][elindex])/2;	    
	    }
	}
    }
  return 0;
}
      

//********************************************************
int test_data()
{

  for (azindex=0; azindex<3600; azindex++)
    {
      for (elindex=0; elindex<900; elindex++)
	{

	  mapx[0][azindex][100]=0.001;
	  mapx[0][azindex][200]=0.00178;
	  mapx[0][azindex][300]=0.00316;
	  mapx[0][azindex][400]=0.00562;
	  mapx[0][azindex][500]=0.01;
	  mapx[0][azindex][600]=0.0178;
	  mapx[0][azindex][700]=0.0316;
	  mapx[0][azindex][800]=0.0562;

    	  mapx[0][300][elindex]=0.00056; 
     	  mapx[0][500][elindex]=0.001;
	  mapx[0][900][elindex]=0.00178;
	  mapx[0][1100][elindex]=0.00316;
	  mapx[0][1400][elindex]=0.00562;
	  mapx[0][1600][elindex]=0.01;
	  mapx[0][1800][elindex]=0.0178;
	  mapx[0][2000][elindex]=0.0316;
	  mapx[0][2200][elindex]=0.0562;
	  mapx[0][2400][elindex]=0.1;



	}
    }
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
  float mapplot[720][180];

  int i=0, j=0, k=0;
  float tr[6]= {0.0, 0.5, 0.0, 0.0, 0.0, 0.5};

  float fmin=1, fmax=0;
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
  fmax=0.1;
  cpgslct(pg_id);
  cpgeras();
  cpgenv(0.0, 360, 0.0, 90, 1.0, -2); 
    cpglab("Azimuth", "Elevation", "Antenna Power Pattern  [Data: May 7-22, 2006]");
  cpgctab(RL, RR, RG, RB, 9, contra, bright);
    cpgimag(f, (float)nx, (float)ny, 1.0, (float)nx, 1.0, (float)ny,  fmin, fmax, tr);
  cpgbox("BCNST1",0.0,0,"BCNST1",0.0,0);
     return 0;
}
