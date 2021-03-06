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
  int satid;
  double wstart;
  double wstop;
  int chan;
} satpasses[1000];

  struct
  {
    int satfmnum;
    double dyear;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    long satorbitnum;
    float meananom;
    char station [3];
    float azimuth;
    float elevation;
    float range;
    int satchannel;
    int fftbincenter;
    float bin1[8];
    float bin2[8];
    float bin3[8];
    float bin4[8];
    float noisebin1[10];
    float noisebin2[10];
    float noisebin3[10];
    float noisebin4[10];
    float tot1;
    float tot2;
    float tot3;
    float tot4;
  } aq;


struct
{
  int weight[901];
  float ratio1[901];
  float ratio2[901];
} mapAzimuth[3601];
//Round to the nearest 1/10 degree.

//Function Prototypes

int read_passinfo(void);
int read_satpower(void);
int write_data(void);
int write_noise_data(void);
int write_map12(void);
int write_map34(void);

//Global Variables
int totsatpassid;
float channel1, channel2, channel3, channel4;
int azIndex, elIndex;

//Files
char passfilename[60];
char satpowerfilename[60];
//char *listname="listpowerfiles_Z02";
//char *listname="listpowerfiles_20degE";
//char *listname="listpowerfiles_Null1";
char *listname;//="listpowerfiles_Null2";
char runningfile[35];
char includepassdata[60];
char noisefile[60];
char *mapfile12="mapfile12";
char *mapfile34="mapfile34";

FILE *passfile;
FILE *satpowerfile;
FILE *fp1;
FILE *pass;
FILE *noise;
FILE *map12;
FILE *map34;


//********************************************************

int main(int argc, char *argv[])
{
  int listmax;
  int filecycles;

   if (argc != 2){
    printf( "usage: %s listfilename\n", argv[0] );
    exit(1);
  }

  listname = argv[1];

  printf("opening acqnamefile: '%s'\n",listname);

 if ((fp1=fopen(listname,"r"))==NULL)
	{
	  printf("Cannot open acqname file. \n");
	  exit(1);
	}
     fscanf(fp1,"%i",&listmax);

     fscanf(fp1,"%s",passfilename);

     fscanf(fp1,"%s", includepassdata);

     fscanf(fp1,"%s", noisefile);

     printf("Reading pass file %s ...\n",passfilename);
  read_passinfo();


   for (filecycles=0; filecycles<listmax; filecycles++)
    {
      fscanf(fp1,"%s",satpowerfilename);
      printf("Reading sat power file %s ...\n", satpowerfilename);
      read_satpower();
    }
   // printf("Writing map12 file ...\n");
   // write_map12();
   // printf("Writing map34 file ...\n");
   // write_map34();
   // fclose(fp1);
   printf("End of Program\n");
  return 0;
}

//********************************************************
int read_passinfo()
{
  int i=0;

  if ((passfile=fopen(passfilename,"r"))==NULL)
    {
    printf("Cannot open pass file. \n");
  exit(1);
    }

  while (feof(passfile)==0)
    {
      i++;
      fscanf(passfile, "%d %lf %lf %d \n", &satpasses[i].satid, &satpasses[i].wstart, &satpasses[i].wstop, &satpasses[i].chan);

    }
  totsatpassid=i;
  //  printf("There are %d entries. \n", i);

  fclose(passfile);

  return 0;
}

//********************************************************
int read_satpower()
{
  int i, j, k, b, n;
  int acqnum;
  char acqstr[12];
  char timemark[3];
  char dayofweek[3];
  char strmonth[3];
  int date;
  int hour;
  int minute;
  int second;
  int year;
  float fftbin1[515], fftbin2[515], fftbin3[515], fftbin4[515];
  char tmp1[8], tmp2[10], tmp3[10], tmp4[10], tmp5[10], tmp6[10], tmp7[10], tmp8[10], tmp9[10];
  double dyear;
  int month=0, mlen=0, maccum=0;
  int centerbin;
  int fftcenterbinsofvisiblesats[20];
  float temp1,temp2,temp3,temp4;
  int visiblesatnum;

struct
{
  char satname[5];
  int satnum;
  float azimuth;
  float elevation;
  float  range;
  float velocity;
  float meananom;
  long orbitnum;
} satinfo[10];

  if ((satpowerfile=fopen(satpowerfilename,"r"))==NULL)
    {
    printf("Cannot open sat power file. \n");
  exit(1);
    }

  while (feof(satpowerfile)==0)
    {
      fscanf(satpowerfile, "%s%d",acqstr, &acqnum);
      fscanf(satpowerfile, "%s%s%s%d%d:%d:%d%d", timemark, dayofweek, strmonth, &date, &hour, &minute, &second, &year);

	  if (strcmp(strmonth, "Jan")==0) { month=1; mlen=31; maccum=0;}
	  else if (strcmp(strmonth, "Feb")==0){month=2; mlen=28; maccum=31;}
	  else if (strcmp(strmonth, "Mar")==0){month=3; mlen=31; maccum=59;}
	  else if (strcmp(strmonth, "Apr")==0){month=4; mlen=30; maccum=90;}
	  else if (strcmp(strmonth, "May")==0){month=5; mlen=31; maccum=120;}
	  else if (strcmp(strmonth, "Jun")==0){month=6; mlen=30; maccum=151;}
	  else if (strcmp(strmonth, "Jul")==0){month=7; mlen=31; maccum=181;}
	  else if (strcmp(strmonth, "Aug")==0){month=8; mlen=31; maccum=212;}
	  else if (strcmp(strmonth, "Sep")==0){month=9; mlen=30; maccum=243;}
	  else if (strcmp(strmonth, "Oct")==0){month=10;mlen=31; maccum=273;}
	  else if (strcmp(strmonth, "Nov")==0){month=11;mlen=30; maccum=304;}
	  else if (strcmp(strmonth, "Dec")==0){month=12;mlen=31; maccum=334;}
	  else
	    {
	      printf("No option selected.");
	    }
	  dyear=year+ ((double)maccum + (double)date + ((double)hour+(double)minute/60+(double)second/3600)/24)/365;
	  i=1;
	  fscanf(satpowerfile, "%s", satinfo[i].satname);
	  while (strcmp(satinfo[i].satname, "Bin")!=0)
	    {
	      sscanf(satinfo[i].satname, "FM%d*",&satinfo[i].satnum);
	      fscanf(satpowerfile, "%f%f%f%f%f%ld", &satinfo[i].azimuth, &satinfo[i].elevation, &satinfo[i].range, &satinfo[i].velocity, &satinfo[i].meananom, &satinfo[i].orbitnum);
	      i++;	
	      fscanf(satpowerfile, "%s", satinfo[i].satname);
	    }
	  //  printf("Reading junk ...\n");
	  fscanf(satpowerfile,"%s\n %s %s %s %s %s %s %s %s\n", tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9);

  aq.tot1=0; aq.tot2=0; aq.tot3=0; aq.tot4=0;
  for (b=1; b<513; b++)
    {
      fscanf(satpowerfile, "%f %f %f %f", &fftbin1[b], &fftbin2[b], &fftbin3[b], &fftbin4[b]);
      aq.tot1 += fftbin1[b]*fftbin1[b];
      aq.tot2 += fftbin2[b]*fftbin2[b];
      aq.tot3 += fftbin3[b]*fftbin3[b];
      aq.tot4 += fftbin4[b]*fftbin4[b];
    }


	  // prepare data for storage
  //  printf("Preparing data storage ...\n");
	      aq.dyear=dyear;
	      aq.month = month;
	      aq.day = date;
	      aq.hour = hour;
	      aq.min = minute;
	      aq.sec = second;


    for (j=1; j<(totsatpassid+1); j++){ // for all sats
		  
      for (k=1; k<i; k++){ // for all passes

        // check if the current time is between the pass start and end time
		    if ((dyear>satpasses[j].wstart) && (dyear< satpasses[j].wstop) && (satpasses[j].satid==satinfo[k].satnum)){
  			  aq.satfmnum=satinfo[k].satnum;
  			  aq.satorbitnum=satinfo[k].orbitnum;
  			  aq.meananom=satinfo[k].meananom;
  			  sprintf(aq.station, "GB");
  			  aq.azimuth=satinfo[k].azimuth;
  			  aq.elevation=satinfo[k].elevation;
  			  aq.range=satinfo[k].range;
  			  aq.satchannel=satpasses[j].chan;
  			  centerbin = (int)((float) aq.satchannel*2.5*512/1000);
  			  aq.fftbincenter=centerbin;


  			  aq.bin1[1]=fftbin1[centerbin-3];
  			  aq.bin1[2]=fftbin1[centerbin-2];
  			  aq.bin1[3]=fftbin1[centerbin-1];
  			  aq.bin1[4]=fftbin1[centerbin];
  			  aq.bin1[5]=fftbin1[centerbin+1];
  			  aq.bin1[6]=fftbin1[centerbin+2];
  			  aq.bin1[7]=fftbin1[centerbin+3];

  			  aq.bin2[1]=fftbin2[centerbin-3];
  			  aq.bin2[2]=fftbin2[centerbin-2];
  			  aq.bin2[3]=fftbin2[centerbin-1];
  			  aq.bin2[4]=fftbin2[centerbin];
  			  aq.bin2[5]=fftbin2[centerbin+1];
  			  aq.bin2[6]=fftbin2[centerbin+2];
  			  aq.bin2[7]=fftbin2[centerbin+3];

  			  aq.bin3[1]=fftbin3[centerbin-3];
  			  aq.bin3[2]=fftbin3[centerbin-2];
  			  aq.bin3[3]=fftbin3[centerbin-1];
  			  aq.bin3[4]=fftbin3[centerbin];
  			  aq.bin3[5]=fftbin3[centerbin+1];
  			  aq.bin3[6]=fftbin3[centerbin+2];
  			  aq.bin3[7]=fftbin3[centerbin+3];

  			  aq.bin4[1]=fftbin4[centerbin-3];
  			  aq.bin4[2]=fftbin4[centerbin-2];
  			  aq.bin4[3]=fftbin4[centerbin-1];
  			  aq.bin4[4]=fftbin4[centerbin];
  			  aq.bin4[5]=fftbin4[centerbin+1];
  			  aq.bin4[6]=fftbin4[centerbin+2];
  			  aq.bin4[7]=fftbin4[centerbin+3];

  			  write_data();


    		  channel1=0;
    		  channel2=0;
    		  channel3=0;
    		  channel4=0;

    		  for (n=1; n<8; n++) channel1=channel1+aq.bin1[n];
    		  for (n=1; n<8; n++) channel2=channel2+aq.bin2[n];
    		  for (n=1; n<8; n++) channel3=channel3+aq.bin3[n];
    		  for (n=1; n<8; n++) channel4=channel4+aq.bin4[n];

    		  azIndex=(int) rintf(10*aq.azimuth);
    		  elIndex=(int) rintf(10*aq.elevation);
    		  //printf("%d %d\n", azIndex, elIndex);

    		  mapAzimuth[azIndex].ratio1[elIndex]=(channel1*channel1/(50*2))/(channel2*channel2/(50*2));
    		  mapAzimuth[azIndex].ratio2[elIndex]=(channel3*channel3/(50*2))/(channel4*channel4/(50*2));

    		  //   printf("Processing satellite %d \n", satinfo[k].satnum);

        }
		  }
		}
  }
	
  fclose(satpowerfile);
	return 0;
}

//********************************************************
int write_data()
{

  sprintf(runningfile, "%s%d", includepassdata, aq.satfmnum);
  //printf("filename is %s \n", runningfile);

  if ((pass=fopen(runningfile,"a"))==NULL)
    {
      printf("Cannot open include pass file.\n" );
      exit(1);
    }

fprintf(pass, "%02d/%02d/%4d %02d:%02d:%02d %2d %4.12f %8ld %3.2f %3s %3.3f %3.3f %4.2f %3d %3d %2.6f %2.6f %2.6f %2.6f\n %.6f %.6f %.6f %.6f %.6f %.6f %.6f\n %.6f %.6f %.6f %.6f %.6f %.6f %.6f\n %.6f %.6f %.6f %.6f %.6f %.6f %.6f\n %.6f %.6f %.6f %.6f %.6f %.6f %.6f\n",aq.month,aq.day,(int)floor(aq.dyear),aq.hour,aq.min,aq.sec,aq.satfmnum, aq.dyear, aq.satorbitnum, aq.meananom, aq.station, aq.azimuth, aq.elevation, aq.range, aq.satchannel, aq.fftbincenter, aq.tot1,aq.tot2,aq.tot3,aq.tot4, aq.bin1[1],aq.bin1[2],aq.bin1[3],aq.bin1[4],aq.bin1[5],aq.bin1[6],aq.bin1[7], aq.bin2[1],aq.bin2[2],aq.bin2[3],aq.bin2[4],aq.bin2[5],aq.bin2[6],aq.bin2[7],aq.bin3[1],aq.bin3[2],aq.bin3[3],aq.bin3[4],aq.bin3[5],aq.bin3[6],aq.bin3[7], aq.bin4[1],aq.bin4[2],aq.bin4[3],aq.bin4[4],aq.bin4[5],aq.bin4[6],aq.bin4[7]); 

  fclose(pass);
return 0;
}

