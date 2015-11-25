
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void main(void)
{
	///int epochtime,nleaps,gpstime;
/*
	int epochtime = (int)time(NULL);
	int nleaps = 17;
	int gpstime = epochtime - 315964800 + nleaps;

	printf("Timestamp: %d\nGPS time: %d\n",(int)time(NULL),gpstime);


	  struct timeval tv;

	double curtime;

	gettimeofday(&tv, NULL); 
	curtime=tv.tv_sec + tv.tv_usec/1000000.;
	printf("curtime: %f\n",curtime);
*/

        struct timeval tv;
        gettimeofday(&tv, NULL);
        double epochtime = tv.tv_sec + tv.tv_usec/1000000.;
        double gpstime = epochtime - 315964800. + 17;

        printf("%f\n",gpstime);
}


