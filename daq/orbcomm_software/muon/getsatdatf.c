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

//prototypes
int  acquire_data(void);
void show_channel_data( U16 *bufB, int num_chan );
int plot_channel_data(void);
void transfer_and_scale(U16 *bufA, int num_chan );
int connectsock(char *host, char *service, char *protocol);
void get_response(int sock, char *bufC);
char *send_command0(char *host, char *command);
char *send_command1(char *host, char *command);
int getSatInfo0(void);
int getSatInfo1(void);
int postfft(void);
int plot_freq_data(float accumFD[256]);

U16 channel=0;  //1 channels
U16 range=AD_B_1_V;
char *file_name="satdata.txt";
U32 read_count;
U32  mem_size = 0;
F64 sample_rate=5000000;
U16 * ai_buf;
float voltarray[10000000];
int pg_id;
char string[625];
int scanNum, acqmax;
FILE *fp, *fp1;
int max_scans=50000;

double *timedata;
fftw_complex *freqdata;
fftw_plan p;
int N=512;
char *acqname="acqFiles";
char fname[60];


//********************************************************

int main(void)
{
  int j, jj;
  char bufD[128];
  int ind, Mcount,acqcycles;
  //  int M=50;
  int M=50;
  int plan;
  int k, kk;
  float accumFreqData[256]; 

   pg_id = cpgopen("/XWINDOW");
   cpgpap(6.00, 0.8);
   cpgpage();
   cpgslct(pg_id);
   cpgsci(1);
   cpgsvp(0.15f, 0.95f, 0.2f, 0.8f);
   cpgswin(0, 257.0f, 0.0f, 0.005f);
   cpgsch(2.0);

     if ((fp1=fopen(acqname,"r"))==NULL)
	{
	  printf("Cannot open acqname file. \n");
	  exit(1);
	}
   
     fscanf(fp1,"%i",&acqmax);
   for (acqcycles=0; acqcycles<acqmax; acqcycles++)
    {
      fscanf(fp1,"%s",fname);
  timedata = fftw_malloc(sizeof(double) * (N+1));
  freqdata = fftw_malloc(sizeof(fftw_complex) * (N+1));
  read_count=N*M;
  mem_size=read_count * 2;
  ai_buf = (I16*)malloc(mem_size);
      if ((fp=fopen(fname,"w"))==NULL)
	{
	  printf("Cannot open file. \n");
	  exit(1);
	}
 
  for (j=1; j<=max_scans; j++)
    {
      printf("\n\nAcquisition %d\n",j);
      printf("File: %s\n",fname);
      fprintf(fp,"\nAcquisition: %d\n",j);
      strcpy(bufD, send_command0("Apollo","GET_TIME$"));
      printf("Universal Time: %s",bufD);
      fprintf(fp, "UT: %s",bufD);
      printf("Satellites above local horizon:\n");
      getSatInfo0();
      getSatInfo1();
      acquire_data();
      transfer_and_scale((U16*)ai_buf, channel+1);

      for (k=0; k<(N/2); k++) accumFreqData[k]=0;      

            for (Mcount=1; Mcount<=M; Mcount++)
	      {
		for (ind=0; ind<N; ind++) timedata[ind]=voltarray[ind+(N*(Mcount-1))];
		plan=(j==1)&&(Mcount==1);
		if (plan) p=fftw_plan_dft_r2c_1d(N, timedata, freqdata, FFTW_FORWARD);
		fftw_execute(p);
		for (kk=0; kk<(N/2); kk++)
		  {
		    accumFreqData[kk]+=(sqrt(freqdata[kk][0]*freqdata[kk][0]+freqdata[kk][1]*freqdata[kk][1])/(M*256));	  
		  } 
	      }
	    fprintf(fp, "Bin Voltages \n");

	    for (jj=0; jj<(N/2); jj++) fprintf(fp, "%f\n", accumFreqData[jj]);
	    
	    //      plot_channel_data();
	    plot_freq_data(accumFreqData);
    }
  int fclose(FILE *fp);
  postfft();
  free( ai_buf );
  printf("\n\nEnd of program. "); 
  //getch(); 
  putchar('\n');
    }
  return 0;
}

//********************************************************

int acquire_data()
{
    I16 card, err;

    setbuf( stdout, NULL );
    //    printf("This program inputs %ld data from CH-0 to CH-%d of PCI-9812 in %d Hz, and\nstore data to file '%s'.\nPlease press any key to start the operation.\n", read_count, channel, (int)sample_rate, file_name);

    //    getch();
    if ((card=Register_Card (PCI_9812, 0)) <0 ) {
        printf("Register_Card error=%d\n", card);
        exit(1);
    }
    err = AI_9812_Config(card, P9812_TRGMOD_SOFT, P9812_TRGSRC_CH0, P9812_TRGSLP_POS, P9812_AD2_GT_PCI|P9812_CLKSRC_INT, 0x80, 0);
    if (err!=0) {
       printf("AI_9812_Config error=%d", err);
       exit(1);
    }
    err = AI_AsyncDblBufferMode(card, 0);
    if (err!=0) {
       printf("AI_DblBufferMode error=%d", err);
       exit(1);
    }
    usleep(100);
    err = AI_ContScanChannels(card, channel, range, ai_buf, read_count, sample_rate, SYNCH_OP);
    if (err!=0) {
       printf("AI_ContReadChannel error=%d", err);
       free( ai_buf );
       Release_Card(card);
       exit(1);
    }

    printf("%ld data samples transfered.\n", read_count );
    usleep(100);
    Release_Card(card);
    return 0;
}

void transfer_and_scale(U16 *bufA, int num_chan )
{
  U16 tmp;
  static int adrange=32752;
  U32 i;

  for(i=0; i<read_count; i+=num_chan){
    tmp=bufA[i];
    if (tmp < 0x8000)
      {
	voltarray[i]= (float)tmp/adrange;
      }
    else
      {
	tmp=0xffff-tmp;
	voltarray[i]=((float)tmp/adrange)*(-1);	
      } 
  }
} 

void show_channel_data( U16 *bufB, int num_chan )
{
  U16 adinput;
  int channel_no, chan_idx;
  U32 i, kb;

  for( chan_idx = 0; chan_idx< num_chan; chan_idx++ ){
      printf(" >>>>>>>>>>>>>>> the first 240 data from Channel#%d  <<<<<<<<<<<<<<< \n", chan_idx+1 );
   for( i = 0, kb=0; i< read_count && kb< 240 ; i++ ){
      adinput = bufB[i];
      channel_no = i% num_chan;
		  adinput = adinput >>4;

      if( channel_no == chan_idx ){
     	  printf("%04x  ", adinput );
     	  if( (kb+1)%12 == 0 ) putchar('\n');
        kb++;
      }
    }

    if( chan_idx < num_chan -1 ){
          printf("press any key for next channel:\n");getch();
    }
  }

}

int plot_channel_data(void)
{
  int samp=0;

  printf("Plotting ...");
  cpgask(0);
  cpgpage();
  cpgslct(pg_id);
  cpgsci(3);
  cpgeras();
  cpgsvp(0.15f, 0.95f, 0.2f, 0.8f);
  cpgupdt();
  cpgsch(2.0);
  cpgswin(0, read_count, -0.01f, 0.01f);
  cpgbox("BC1NST",0.0,0,"BCNST",0.0,0);
  cpglab("Time [samples]", "Voltage [volts]", "Antenna Measurement Receiver");
  cpgmove(samp, voltarray[0]);
  for (samp=2; samp<read_count; samp++)
	 {
	   cpgdraw(samp, voltarray[samp]);
	 }
  return 0;
}


int plot_freq_data(float accumFD[256])
{
  int bin=0;
  cpgeras();
  //  cpgswin(80, 120, 0.0f, 0.01f);
  cpgbox("BC1NST",0.0,0,"BCNST",0.0,0);
  cpglab("Frequency [bins]", "Peak Voltage [volts]", "Antenna Measurement Receiver");
  cpgmove(bin, accumFD[0]);
  for (bin=1; bin<(N/2); bin++)
	 {
	   cpgdraw(bin, accumFD[bin]);
	 }
  return 0;
}

int connectsock(char *host, char *service, char *protocol)
{
	/* This function is used to connect to the server.  "host" is the
	   name of the computer on which PREDICT is running in server mode.
	   "service" is the name of the socket port.  "protocol" is the
	   socket protocol.  It should be set to UDP. */

	struct hostent *phe;
	struct servent *pse;
	struct protoent *ppe;
	struct sockaddr_in sin;
	
	int s, type;
	
	bzero((char *)&sin,sizeof(struct sockaddr_in));
	sin.sin_family=AF_INET;
	
	if ((pse=getservbyname(service,protocol)))
		sin.sin_port=pse->s_port;

	else if ((sin.sin_port=htons((unsigned short)atoi(service)))==0)
	{
		printf("Can't get services\n");
		return -1;
	}

	if ((phe=gethostbyname(host)))
		bcopy(phe->h_addr,(char *)&sin.sin_addr,phe->h_length);

	else if ((sin.sin_addr.s_addr=inet_addr(host))==INADDR_NONE)
	{
		printf("Can't get host: \"%s\".\n",host);
		return -1;
	}
	
	if ((ppe=getprotobyname(protocol))==0)
		return -1;

	if (strcmp(protocol,"udp")==0)
		type=SOCK_DGRAM;
	else
		type=SOCK_STREAM;
	
	s=socket(PF_INET,type,ppe->p_proto);

	if (s<0)
	{
		printf("Can't get socket.\n");
		return -1;
	}

	if (connect(s,(struct sockaddr *)&sin,sizeof(sin))<0)
	{
		printf("Can't connect to socket.\n");
		return -1;
	}

	return s;
}

void get_response(int sock, char *bufC)
{
	/* This function gets a response from the
	   server in the form of a character string. */

	int n;

	n=read(sock,bufC,625);

	if (n<0)
	{
		if (errno==EINTR)
			return;

		if (errno==ECONNREFUSED)
		{
			fprintf(stderr, "Connection refused - PREDICT server not running\n");
			exit (1);
		}
	}

	bufC[n]='\0';
}

char *send_command0(host, command)
char *host, *command;
{
	int sk;

	/* This function sends "command" to PREDICT running on
	   machine "host", and returns the result of the command
	   as a pointer to a character string. */

	/* Open a network socket */
	sk=connectsock(host,"predict0","udp");

	if (sk<0)
	  {
	    printf("ERROR Socket 0\n");
	    exit(1);
	  }

	/* Build a command buffer */
	sprintf(string,"%s\n",command);

	/* Send the command to the server */
   	write(sk,command,strlen(string));

	/* clear string[] so it can be re-used for the response */
	string[0]=0;

	/* Get the response */
   	get_response(sk,string);

	/* Close the connection */
   	close(sk);

	return string;
}

char *send_command1(host, command)
char *host, *command;
{
	int sk1;

	/* This function sends "command" to PREDICT running on
	   machine "host", and returns the result of the command
	   as a pointer to a character string. */

	/* Open a network socket */
	sk1=connectsock(host,"predict1","udp");

	if (sk1<0)
	  {
	    printf("ERROR Socket 1\n");
	    exit(1);
	  }

	/* Build a command buffer */
	sprintf(string,"%s\n",command);

	/* Send the command to the server */
   	write(sk1,command,strlen(string));

	/* clear string[] so it can be re-used for the response */
	string[0]=0;

	/* Get the response */
   	get_response(sk1,string);

	/* Close the connection */
   	close(sk1);

	return string;
}

int getSatInfo0()
{
	int x, y, z, satnum;
	char buf[128], command[128], satlist[625], satname[26],
	     visibility, satnamelist[26][26], event[15], squint_string[15];
	long aostime, orbitnum;
	float az, el, slong, slat, footprint, range, altitude,
	      velocity, phase, eclipse_depth, squint;
	time_t t;

	/* Get the list of satellite names from PREDICT */

	strcpy(satlist, send_command0("Apollo","GET_LIST"));

	//printf("\nPREDICT returned the following string in response to GET_LIST:\n%s\n",satlist);

	/* Parse the response and place each name
	   in the character array satnamelist[]. */


	for (x=0, y=0, z=0; y<strlen(satlist); y++)
	{
		if (satlist[y]!='\n')
		{
			satnamelist[z][x]=satlist[y];
			x++;
		}

		else
		{
			satnamelist[z][x]=0;
			z++;
			x=0;
		}
	}


	satnum=16; //SET TO MAXIMUM NUMBER OF SATELLITES

	for (z=0; z<satnum; z++)
	{
		sprintf(command,"GET_SAT %s",satnamelist[z]);
		strcpy(buf, send_command0("Apollo",command));
		// printf("The following string was returned in response to %s:\n%s\n",command,buf);

		/* Parse the response from GET_SAT */

		/* The first element of the response is the satellite name.
		   It is ended with a '\n' character and many contain spaces. */

		for (x=0; buf[x]!='\n'; x++)
			satname[x]=buf[x];

		satname[x]=0;
		x++;

		/* The rest of the data from GET_SAT is numerical, and
		   can be parsed using the sscanf() function.  First, the
		   satellite name is removed from "buf", and then "buf"
		   is parsed for numerical data using an sscanf(). */

		for (y=0; buf[x+y]!=0; y++)
			buf[y]=buf[x+y];

		buf[y]=0;
 
		sscanf(buf,"%f %f %f %f %ld %f %f %f %f %ld %c %f %f %f",&slong,&slat,&az,&el,&aostime,&footprint,&range,&altitude,&velocity,&orbitnum,&visibility,&phase,&eclipse_depth,&squint);

		t=(time_t)aostime;

		if (el>0.0)
			strcpy(event,"LOS at");

		else
			strcpy(event,"Next AOS at");

		if (squint==360.0)
			sprintf(squint_string,"N/A");
		else
			sprintf(squint_string,"%.2f degrees",squint);
		

		if (el >= 0.0)
		  {
		    printf("   %s %.2f %.2f %.2f\n", satname,az,el,range);
		    fprintf(fp,"%s %.2f %.2f %.2f\n", satname,az,el,range);
		  }
		    
		/*		printf("Values are as follows:\nName: %s\nLong: %.2f degrees\nLat: %.2f degrees\nAz: %.2f degrees\nEl: %+-6.2f degrees\n%s: %ld = %sFootprint: %.2f km\nRange: %.2f km\nAltitude: %.2f km\nVelocity: %.2f km/hr\nEclipse Depth: %.2f\nPhase: %.2f\nSquint: %s\nOrbit #: %ld\n\n",satname,slong,slat,az,el,event,aostime,asctime(gmtime(&t)),footprint,range,altitude,velocity,eclipse_depth,phase,squint_string,orbitnum);  		 */

 	}
		return 0;
}
int getSatInfo1()
{
	int x, y, z, satnum;
	char buf[128], command[128], satlist[625], satname[26],
	     visibility, satnamelist[26][26], event[15], squint_string[15];
	long aostime, orbitnum;
	float az, el, slong, slat, footprint, range, altitude,
	      velocity, phase, eclipse_depth, squint;
	time_t t;

	/* Get the list of satellite names from PREDICT */

	strcpy(satlist, send_command1("Apollo","GET_LIST"));

	//printf("\nPREDICT returned the following string in response to GET_LIST:\n%s\n",satlist);

	/* Parse the response and place each name
	   in the character array satnamelist[]. */


	for (x=0, y=0, z=0; y<strlen(satlist); y++)
	{
		if (satlist[y]!='\n')
		{
			satnamelist[z][x]=satlist[y];
			x++;
		}

		else
		{
			satnamelist[z][x]=0;
			z++;
			x=0;
		}
	}


	satnum=19; //SET TO MAXIMUM NUMBER OF SATELLITES

	for (z=0; z<satnum; z++)
	{
		sprintf(command,"GET_SAT %s",satnamelist[z]);
		strcpy(buf, send_command1("Apollo",command));
		// printf("The following string was returned in response to %s:\n%s\n",command,buf);

		/* Parse the response from GET_SAT */

		/* The first element of the response is the satellite name.
		   It is ended with a '\n' character and many contain spaces. */

		for (x=0; buf[x]!='\n'; x++)
			satname[x]=buf[x];

		satname[x]=0;
		x++;

		/* The rest of the data from GET_SAT is numerical, and
		   can be parsed using the sscanf() function.  First, the
		   satellite name is removed from "buf", and then "buf"
		   is parsed for numerical data using an sscanf(). */

		for (y=0; buf[x+y]!=0; y++)
			buf[y]=buf[x+y];

		buf[y]=0;
 
		sscanf(buf,"%f %f %f %f %ld %f %f %f %f %ld %c %f %f %f",&slong,&slat,&az,&el,&aostime,&footprint,&range,&altitude,&velocity,&orbitnum,&visibility,&phase,&eclipse_depth,&squint);

		t=(time_t)aostime;

		if (el>0.0)
			strcpy(event,"LOS at");

		else
			strcpy(event,"Next AOS at");

		if (squint==360.0)
			sprintf(squint_string,"N/A");
		else
			sprintf(squint_string,"%.2f degrees",squint);
		

		if (el >= 0.0)
		  {
		    printf("   %s %.2f %.2f %.2f\n", satname,az,el,range);
		    fprintf(fp,"%s %.2f %.2f %.2f\n", satname,az,el,range);
		  }
		    
		/*		printf("Values are as follows:\nName: %s\nLong: %.2f degrees\nLat: %.2f degrees\nAz: %.2f degrees\nEl: %+-6.2f degrees\n%s: %ld = %sFootprint: %.2f km\nRange: %.2f km\nAltitude: %.2f km\nVelocity: %.2f km/hr\nEclipse Depth: %.2f\nPhase: %.2f\nSquint: %s\nOrbit #: %ld\n\n",satname,slong,slat,az,el,event,aostime,asctime(gmtime(&t)),footprint,range,altitude,velocity,ec
lipse_depth,phase,squint_string,orbitnum);  		 */

 	}
		return 0;
}

int postfft()
{
  fftw_destroy_plan(p);
  fftw_free(timedata); fftw_free(freqdata);
 return 0;
}    
