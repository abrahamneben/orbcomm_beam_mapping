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

#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)

//Structures

struct
{
  int weight[901];
  float ratio1[901];
  float ratio2[901];
} mapAzimuth[3601];

struct
{
  int weight1[181];
  int weight2[181];
  float ratio1[181];
  float ratio2[181];
} mapLowResAzimuth[721];




//Global Variables
int totsatpassid;
float channel1, channel2, channel3, channel4;
int azIndex, elIndex;

//Function Prototypes

int read_map12(void);
int scale_map12(void);
int write_map12(void);
int read_map34(void);
int scale_map34(void);
int write_map34(void);




//Files
char passfilename[60];
char satpowerfilename[60];
char *listname="listpowerfiles";
char runningfile[35];
char includepassdata[60];
char noisefile[60];
char *mapfile12="mapfile12";
char *mapfile34="mapfile34";
char *mapfile12L="mapfile12L";
char *mapfile34L="mapfile34L";

FILE *passfile;
FILE *satpowerfile;
FILE *fp1;
FILE *pass;
FILE *noise;
FILE *map12;
FILE *map34;
FILE *map12L;
FILE *map34L;


//********************************************************

int main(void)
{
  int listmax;
  int filecycles;

   read_map12();
   scale_map12();
   write_map12();

   read_map34();
   scale_map34();
   write_map34();


   printf("End of Program\n");
  return 0;
}

//********************************************************
int read_map12()
{
  int az, el;
float az1, el1;

  printf("Reading map12 file ...\n");

  if ((map12=fopen(mapfile12,"r"))==NULL)
    {
      printf("Cannot open map12 file.\n" );
      exit(1);
    }
  for (az=0; az< 3600; az++)
    {
      for (el=0; el< 901; el++)
	{

	  fscanf(map12, "%f %f %f",&az1, &el1,  &mapAzimuth[az].ratio1[el]);
	  //	  printf("%.1f %.1f %.6f\n",az1, el1,  mapAzimuth[az].ratio1[el]);
	}
    }
  fclose(map12);
return 0;
}

//********************************************************
int scale_map12()
{
  int az, el;
  int newaz, newel;
  int i,j;
  int step=5;
  int count;
  float sum;

  printf("Scaling mapfile 12 ...\n");

  az=0;
  el=0;
  for (newaz=0; newaz<720; newaz++)
    {
      az=newaz*step;
 
      for (newel=0; newel<181; newel++)
	{
	  el=newel*step;
	  sum=0;
	  count=0;
	  for (i=(az-step); i<(az+step); i++)
	    {
	      for (j=(el-step); j<(el+step); j++)
		{
		  //printf("%d %d %.6f\n",i, j,  mapAzimuth[i].ratio1[j]);
		  if (mapAzimuth[i].ratio1[j]>0)
		    {
		      sum=sum + mapAzimuth[i].ratio1[j];
		      count++;
		    }
		}
	    }
	  if (count == 0)
	    {
	     mapLowResAzimuth[newaz].ratio1[newel] = 0;	
	     mapLowResAzimuth[newaz].weight1[newel] = count;
	    } 
	  else
	    {
	      mapLowResAzimuth[newaz].ratio1[newel] = sum/(float)count;	
	     mapLowResAzimuth[newaz].weight1[newel] = count;
	    }
	  // printf("%.2f %.2f, %.8f %d, %.8f\n", (float)newaz/2, (float)newel/2, sum, mapLowResAzimuth[newaz].weight1[newel], mapLowResAzimuth[newaz].ratio1[newel]);
	}
      
    }
  return 0;
}

//********************************************************
int write_map12()
{
  int newaz, newel;

  printf("Writing mapfile12L ...\n");
  if ((map12L=fopen(mapfile12L,"a"))==NULL)
    {
      printf("Cannot open map12L file.\n" );
      exit(1);
    }
  for (newaz=0; newaz< 720; newaz++)
    {
      for (newel=0; newel< 181; newel++)
	{
	  fprintf(map12L,"%.2f %.2f %.8f\n", (float)newaz/2, (float)newel/2, mapLowResAzimuth[newaz].ratio1[newel]);
	}
	  fprintf(map12L,"\n"); 
    }
  fclose(map12L);
return 0;
}

//********************************************************
int read_map34()
{
  int az, el;
float az1, el1;

  printf("Reading map34 file ...\n");

  if ((map34=fopen(mapfile34,"r"))==NULL)
    {
      printf("Cannot open map34 file.\n" );
      exit(1);
    }
  for (az=0; az< 3600; az++)
    {
      for (el=0; el< 901; el++)
	{

	  fscanf(map34, "%f %f %f",&az1, &el1,  &mapAzimuth[az].ratio2[el]);
	  //	  printf("%.1f %.1f %.6f\n",az1, el1,  mapAzimuth[az].ratio2[el]);
	}
    }
  fclose(map34);
return 0;
}

//********************************************************
int scale_map34()
{
  int az, el;
  int newaz, newel;
  int i,j;
  int step=5;
  int count;
  float sum;

  printf("Scaling mapfile 34 ...\n");

  az=0;
  el=0;
  for (newaz=0; newaz<720; newaz++)
    {
      az=newaz*step;
 
      for (newel=0; newel<181; newel++)
	{
	  el=newel*step;
	  sum=0;
	  count=0;
	  for (i=(az-step); i<(az+step); i++)
	    {
	      for (j=(el-step); j<(el+step); j++)
		{
		  //printf("%d %d %.6f\n",i, j,  mapAzimuth[i].ratio2[j]);
		  if (mapAzimuth[i].ratio2[j]>0)
		    {
		      sum=sum + mapAzimuth[i].ratio2[j];
		      count++;
		    }
		}
	    }
	  if (count == 0)
	    {
	     mapLowResAzimuth[newaz].ratio2[newel] = 0;	
	     mapLowResAzimuth[newaz].weight2[newel] = count;
	    } 
	  else
	    {
	      mapLowResAzimuth[newaz].ratio2[newel] = sum/(float)count;	
	     mapLowResAzimuth[newaz].weight2[newel] = count;
	    }
	  // printf("%.2f %.2f, %.8f %d, %.8f\n", (float)newaz/2, (float)newel/2, sum, mapLowResAzimuth[newaz].weight2[newel], mapLowResAzimuth[newaz].ratio2[newel]);
	}
      
    }
  return 0;
}

//********************************************************
int write_map34()
{
  int newaz, newel;

  printf("Writing mapfile34L ...\n");
  if ((map34L=fopen(mapfile34L,"a"))==NULL)
    {
      printf("Cannot open map34L file.\n" );
      exit(1);
    }
  for (newaz=0; newaz< 720; newaz++)
    {
      for (newel=0; newel< 181; newel++)
	{
	  fprintf(map34L,"%.2f %.2f %.8f\n", (float)newaz/2, (float)newel/2, mapLowResAzimuth[newaz].ratio2[newel]);
	}
	  fprintf(map34L,"\n"); 
    }
  fclose(map34L);
return 0;
}

//********************************************************



