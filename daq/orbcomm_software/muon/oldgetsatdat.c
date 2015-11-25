#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dask.h"
#include "conio.h"
#include "cpgplot.h"

#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)

//prototypes
BOOLEAN write_to_file( U16 *buf, int num_chan );
void show_channel_data( U16 *buf, int num_chan );
void plot_channel_data();

U16 channel=0;  //1 channels
U16 range=AD_B_1_V;
char *file_name="satdata.txt";
//U32 read_count=50000, mem_size = 0;
//F64 sample_rate=5000;
//U32 read_count=10000000, mem_size = 0;
U32 read_count=5000, mem_size = 0;
F64 sample_rate=5000000;
I16 * ai_buf;
float voltarray[10000000];




int main(void)
{
    I16 card, err;

    setbuf( stdout, NULL );
    printf("This program inputs %ld data from CH-0 to CH-%d of PCI-9812 in %d Hz, and\nstore data to file '%s'.\nPlease press any key to start the operation.\n", read_count, channel, (int)sample_rate, file_name);

    getch();
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

    mem_size=read_count * 2;
    ai_buf = (I16*)malloc(mem_size);

    err = AI_ContScanChannels(card, channel, range, ai_buf, read_count, sample_rate, SYNCH_OP);
    if (err!=0) {
       printf("AI_ContReadChannel error=%d", err);
       free( ai_buf );
       Release_Card(card);
       exit(1);
    }

    printf(" %ld data trnasfered !\n", read_count );

    Release_Card(card);

	  if( write_to_file( (U16*)ai_buf, channel+1 ) )
        printf("\n\nThe input data is already stored in file '%s'.\n", file_name);

	  //    show_channel_data( (U16*)ai_buf, channel+1 );
    plot_channel_data();
    free( ai_buf );

    printf("\nPress ENTER to exit the program. "); 
    //getch(); 
    //putchar('\n');
    return 0;
}


BOOLEAN write_to_file( U16 *buf, int num_chan )
{
 // int chan_no;
  U8 temp_s[100];
  U16 tmp;
  FILE *fp;
  static int adrange=32752;
  U32 i;
	
  if (( fp = fopen( file_name , "w+b")) == NULL)
	 	return FALSE;

  fprintf( fp, "ContScanChannels with SYNCH_OP mode \n");
  fprintf( fp, "count_per_page:%li\n", read_count );
  fprintf( fp, "channel_num:%d\n", num_chan );
  fprintf( fp, "sample_rate(Hz):%li\n", (U32)sample_rate );
  fprintf( fp, "CH0   CH1   CH2   CH3 \n======================\n");

  for(i=0; i<read_count; i+=num_chan){
    sprintf( temp_s, "%04x   %04x   %04x   %04x\n", buf[i], buf[i+1], buf[i+2], buf[i+3] );
    tmp=buf[i];
    if (tmp < 0x8000)
      {
	voltarray[i]= (float)tmp/adrange;
      }
    else
      {
	tmp=0xffff-tmp;
	voltarray[i]=((float)tmp/adrange)*(-1);	
      }
    //    printf("%1.6f  %i\n",voltarray[i],tmp);
    fwrite(temp_s, sizeof(U8), strlen(temp_s), fp);
  }

  fclose( fp );
  return TRUE;
}

void show_channel_data( U16 *buf, int num_chan )
{
  U16 adinput;
  int channel_no, chan_idx;
  U32 i, k;

  for( chan_idx = 0; chan_idx< num_chan; chan_idx++ ){
      printf(" >>>>>>>>>>>>>>> the first 240 data from Channel#%d  <<<<<<<<<<<<<<< \n", chan_idx+1 );
   for( i = 0, k=0; i< read_count && k< 240 ; i++ ){
      adinput = buf[i];
      channel_no = i% num_chan;
		  adinput = adinput >>4;

      if( channel_no == chan_idx ){
     	  printf("%04x  ", adinput );
     	  if( (k+1)%12 == 0 ) putchar('\n');
        k++;
      }
    }

    if( chan_idx < num_chan -1 ){
          printf("press any key for next channel:\n");getch();
    }
  }

}

void plot_channel_data()
{
  int samp=0;
  int pg_id;

  pg_id = cpgopen("/XSERVE");
  cpgpap(8.0, 0.8);
  cpgask(0);
  cpgpage();
  cpgslct(pg_id);
  cpgsci(3);
  cpgeras();
  cpgsvp(0.15f, 0.95f, 0.2f, 0.8f);
  cpgupdt();
  cpgsch(2.0);
  cpgswin(0, read_count, -0.1f, 0.1f);
  cpgbox("BC1NST",0.0,0,"BCNST",0.0,0);
  cpglab("Time [samples]", "Voltage [volts]", "Antenna Measurement Receiver");
  cpgmove(samp, voltarray[0]);
  for (samp=2; samp<read_count; samp++)
	 {
	   cpgdraw(samp, voltarray[samp]);
	 }
  return 0;
}
