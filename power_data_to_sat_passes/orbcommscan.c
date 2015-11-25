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
    double start;
    double stop;
    int chan;
} sattrack[50];



struct
{
    int month;
    int mlen;
    int maccum;
    int year;
    int date;
    int hour;
    int min;
    int sec;
} tstamp;

struct
{
    int satidnum;
    int chan;
} satinfo;

//Function Prototypes

//Variables
char mode[80];
char junka[80], junkb[80];
char month[3];
int ja,jb;
int satid;
double dyear;
int test=8;
char qtest[1];
char x[1];

double wstart, wstop, wsize=0.0000570776256; //window set for +/- 30 minutes

FILE *satdebug;

char *satdebugfile;//="../data20130226/orbcomm20130226.out";

FILE *pass;
char *passfile;

//********************************************************

int main(int argc, char *argv[])
{
    
    if (argc != 3){
        printf( "usage: %s satdebugfile passinfo\n", argv[0] );
        exit(1);
    }
    
    satdebugfile = argv[1];
    passfile = argv[2];
    
    long i,ip;
    
    if ((satdebug=fopen(satdebugfile, "r"))==NULL)
    {
        printf("Can't open file. \n");
        exit(1);
    }
    
    if ((pass=fopen(passfile,"a+"))==NULL)
    {
        printf("Cannot open file. \n");
        exit(1);
    }
    
    while (feof(satdebug)==0){
        
        while ((strcmp(mode,"Dplr")!=0) && (feof(satdebug)==0)){
            fscanf(satdebug, "%s", mode);
        }
        printf("Found %s \n", mode);
        
        if ((i=ftell(satdebug)) == -1L)
        	printf("A file error has occured. \n");
        
        printf("File pointer is at %ld \n", i);
        
        fseek(satdebug, i-test, SEEK_SET);
        fscanf(satdebug, "%c", qtest);
        printf("Test character is %s \n", qtest);
        if (strcmp(qtest,"?")!=0 && (strcmp(mode,"Dplr")==0)){
            ip=i-48;
            fseek(satdebug, ip, SEEK_SET);
            printf("Pointer now at %ld \n", ip);
            
            fscanf(satdebug, "%s", junka);
            sscanf(junka, "%c", x);
            if ((strcmp(x,"x")==0)){
                ip=i-49;
                fseek(satdebug, ip, SEEK_SET);
                fscanf(satdebug, "%s", junka);
                
            }
            
            printf("%s \n", junka);
            
            fscanf(satdebug, "%s", junkb);
            printf("%s \n", junkb);
            
            fscanf(satdebug, "%d", &satinfo.chan);
            printf("Sat Channel is %d \n", satinfo.chan);
            
            sscanf(junka, "Rx[%d%3s%d", &tstamp.date, month, &tstamp.year);
            
            sscanf(junkb, "%d:%d:%d|%d.%d]Sync(%d", &tstamp.hour, &tstamp.min, &tstamp.sec, &ja, &jb, &satid);
            printf("Hour %d \n", tstamp.hour);
            printf("Minute %d \n", tstamp.min);
            printf("Second %d \n", tstamp.sec);
            
            //      printf("%d %d \n", ja, jb);
            printf("Satellite ID is %d \n", satid);
            
            printf("Date is %d %s %d \n", tstamp.date, month, tstamp.year);
            
            if (strcmp(month, "Jan")==0) {tstamp.month=1;      tstamp.mlen=31; tstamp.maccum=0;}
            else if (strcmp(month, "Feb")==0){tstamp.month=2;  tstamp.mlen=28; tstamp.maccum=31;}
            else if (strcmp(month, "Mar")==0){tstamp.month=3;  tstamp.mlen=31; tstamp.maccum=59;}
            else if (strcmp(month, "Apr")==0){tstamp.month=4;  tstamp.mlen=30; tstamp.maccum=90;}
            else if (strcmp(month, "May")==0){tstamp.month=5;  tstamp.mlen=31; tstamp.maccum=120;}
            else if (strcmp(month, "Jun")==0){tstamp.month=6;  tstamp.mlen=30; tstamp.maccum=151;}
            else if (strcmp(month, "Jul")==0){tstamp.month=7;  tstamp.mlen=31; tstamp.maccum=181;}
            else if (strcmp(month, "Aug")==0){tstamp.month=8;  tstamp.mlen=31; tstamp.maccum=212;}
            else if (strcmp(month, "Sep")==0){tstamp.month=9;  tstamp.mlen=30; tstamp.maccum=243;}
            else if (strcmp(month, "Oct")==0){tstamp.month=10; tstamp.mlen=31; tstamp.maccum=273;}
            else if (strcmp(month, "Nov")==0){tstamp.month=11; tstamp.mlen=30; tstamp.maccum=304;}
            else if (strcmp(month, "Dec")==0){tstamp.month=12; tstamp.mlen=31; tstamp.maccum=334;}
            else
            {
                printf("No option selected.");
            }
            
            //      printf("Month %d has %d days. \n", tstamp.month, tstamp.mlen);
            
            
            dyear=2000+tstamp.year+ ((double)tstamp.maccum + (double)tstamp.date + ((double) tstamp.hour+(double)tstamp.min/60+(double)tstamp.sec/3600)/24)/365;
            
            
            printf("Decimal Year is %4.8f \n", dyear);
            
            wstart=dyear-wsize;
            wstop=dyear+wsize;
            
            printf("Window is from %4.12f to %4.12f \n", wstart, wstop);
            
            
            if ((dyear > sattrack[satid].start) && (dyear < sattrack[satid].stop))
            {
                printf("Save: No \n\n");
            }
            else
            {
                sattrack[satid].start=wstart;
                sattrack[satid].stop=wstop;
                sattrack[satid].chan=satinfo.chan;
                printf("Save: Yes \n\n");
                fprintf(pass, "%2d %4.12f %4.12f %3d \n", satid, sattrack[satid].start, sattrack[satid].stop, sattrack[satid].chan);
                
            }
            
            fseek(satdebug, i, SEEK_SET);
            fscanf(satdebug, "%s", mode);
        }
        else
        {
            fseek(satdebug, i, SEEK_SET);
            fscanf(satdebug, "%s", mode);
            printf("\n");
        }
    }
    
    printf("End of Program\n");
    int fclose(FILE *satdebug);
    int fclose(FILE *pass);
    
    return 0;
}
//********************************************************
//
