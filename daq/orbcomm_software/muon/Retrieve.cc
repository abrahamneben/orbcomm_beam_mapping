// Retrieve.cc
// This module will read data files
//

#include "cpgplot.h"
#include <stdio.h>
#include <comedilib.h>
#include <stdlib.h>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <iomanip>
#include <math.h>
#include <curses.h>


#define BUFSIZE 1000
#define DATASIZE 1730  //1700 + stamp_offset
#define RDATASIZE 1700000  // Max is 1000 samples x 1700 bins
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)


// Function Prototypes
int PlotScan();
int RetrieveData();

static float sqrarg;
int rdata[RDATASIZE];
int buf[BUFSIZE]; 
float scanstore[DATASIZE];

int MAX_SCAN; // Number of scans to record (SET FROM USER INPUT)
unsigned int chanlist[5];
comedi_t *device;
comedi_cmd c,*cmd=&c;
int pg_id;
int rt = 1;
int ret = 100;
int subdev = 0;
int chan = 1;
int range = 3;          // [#2 = -2.5 +2.5]  [#3 = -1.25 1.25]
int aref = AREF_DIFF;
int maxdata;
int size;
int n_scan = 100;  // Maximum of 1000 samples per frequency bin
int n_chan = 1;
int samp_period = 3200; //nanoseconds

long rpoint=0;
int filenumber;
float mean[1701];
float powerDBm[1701];
float freqMHz[1701];
int bin_samples[1000];
int num_bins = 1700;

// Values for -40 dBm analyzer reference line and 10 dB per division
//float vout=0;
//float vstep=0.00488; // DO NOT CHANGE THIS NUMBER!!
long indexA=0;
int scan;
int stamp_offset=30;  //0-9 time & data, 10-14 calibration, 15-24 parameters, 25-19 engineering


////////////////////////////////////////////////////////////////////////
// Start of Main
int main()
{
  cout << endl << "Entering Stored Data Display Mode" << endl << endl;
  pg_id = cpgopen("/XSERVE");
  cpgpap(7.0, 0.65);
  RetrieveData();
return 0;
}
// End of Main
////////////////////////////////////////////////////////////////////////
int PlotScan()
{
  cpgask(0);
  cpgpage();
  cpgslct(pg_id);
  cpgsci(4);
  cpgeras();
  cpgsvp(0.15f, 0.95f, 0.2f, 0.8f);
  cpgupdt();
  cpgsch(2.0);
  cpgswin(15.0, 75.0, -120.0f, -40.0f);
  cpgbox("BC1NST",0.0,0,"BCNST",0.0,0);
  cpglab("Frequency [MHz]", "Power [dBm]", "Solar Radio Burst Spectrometer");
  cpgmove(freqMHz[1], powerDBm[1]);
  for (int bin=2; bin<=num_bins; bin++)
	 {
	   cpgdraw(freqMHz[bin], powerDBm[bin]);
	 }
       return 0;
}


int RetrieveData()
{
  char fname[256];
  int filesize;
  char CHscan[50];
  FILE *infile;
  int counter=1, s_number=0, s_count=0;
  float scanread[DATASIZE];  
  float FRBN_INTERCEPT;
  float FRBN_SLOPE;
  float PWSM_INTERCEPT;
  float PWSM_SLOPE;


  cout << "Start at data file serial number: " ;
  cin >> s_number;
  cout << endl << "Number of sequential scans to view: ";
  cin >> s_count;
  do
    {
      if (s_number == 0)
	{
	  cout << endl << "EXIT" <<endl;
	  break;
	}
      strcpy(fname,"./Data_temp/scan");
      sprintf(CHscan, "%d",  s_number);
      strcat(fname, CHscan);
      infile=fopen(fname,"rb");
      fread(scanread, sizeof(scanread), 1, infile);
      fclose(infile);
      
      FRBN_INTERCEPT = scanread[10];
      FRBN_SLOPE = scanread[11];
      PWSM_INTERCEPT = scanread[12];
      PWSM_SLOPE = scanread[13];

      for (int bin=1; bin<=num_bins; bin++)
	  {

	    powerDBm[bin]=(scanread[bin+stamp_offset-1] - PWSM_INTERCEPT)/PWSM_SLOPE;
	    freqMHz[bin]= ((bin - FRBN_INTERCEPT)/FRBN_SLOPE)/1000;

	  }
	cout << "Now Plotting: " << fname;
	PlotScan();
	cout << endl;

	cout << "Time Stamp: ";
	for (int indexB=0; indexB<=9; indexB++)
	  {
	    cout << scanread[indexB] << "  ";
	  }
	cout << endl;	

	cout << "Equipment Calibration Stamp: ";
	for (int indexB=10; indexB<=14; indexB++)
	  {
	    cout << scanread[indexB] << "  ";
	  }
	cout << endl;	

	cout << "Parameter Stamp: ";
	for (int indexB=15; indexB<=24; indexB++)
	  {
	    cout << scanread[indexB] << "  ";
	  }
	cout << endl;	

	cout << "Engineering Stamp: ";
	for (int indexB=25; indexB<=29; indexB++)
	  {
	    cout << scanread[indexB] << "  ";
	  }

	cout << endl << endl;
	s_number++;
	counter++;
	usleep(500000);
	//	sleep(1);

	if (counter > s_count)
	  {
	    break;
	  }
    }
  while (1);
  cpgclos();
  return 0;
}








