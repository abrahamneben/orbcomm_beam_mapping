#Makefile for viewdata.c

CC = gcc -g

CFLAGS = -I -Wall -Wstrict-prototypes -std=c99
LIBS = -lm

#BINS = orbcommscan
#BINS = findpassdata
BINS = findpassdata4chan
#BINS = findpassdata4chan_fullfft
#BINS = gen_noise_floor_data
#BINS = mapResScale
#BINS = mapInterpolate
#BINS = mapCorrected
#BINS = analyzepass
#BINS = modelpassPT
#BINS = modelpass2
#BINS = modelpass
#BINS = modelpass4chan
#BINS = gaus
#BINS = LSQM
#BINS = spline
#BINS = periodogram
#BINS = periodogramT
#BINS = satmodel
#BINS = satmodelperiod
#BINS = satmodelall
#BINS = satmodeloptimize


all: $(BINS) clean

$(BINS): $(BINS).o
	$(CC) $(LIBS) -o $(BINS) $(BINS).o

$(BINS).o: $(BINS).c
	$(CC) -c $(CFLAGS) $(BINS).c

clean:
	-rm -f $(BINS).o 

clear: 
	-rm -f $(BINS) 


