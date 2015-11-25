#Makefile for gstsatdat.c

CC = gcc
LD = g77

CFLAGS = -I. -I/usr/local/pgplot -L/usr/local/pgplot -Wall -Wstrict-prototypes -O2 -I/usr/local/pci-dask_427/include -I/export/data_1/rbradley/satellite/Sat1/fftw-3.0.1/api
LDFLAGS = -L. -L/usr/local/pgplot -L/usr/X11R6/lib 
LDLIBS =  -lcpgplot -lpgplot -lX11  
LIBS = -lcpgplot -lfftw3 -lm 

#BINS = getsatdatf
#BINS = getsatdat
#BINS = getsatdat2
#BINS = getsatdatf2
#BINS = getsatnew
#BINS = getsatfourchanNOG
BINS = getsatfourchanNG
#BINS = getsatfourchan

all: $(BINS) clean

$(BINS): $(BINS).o conio.o
	$(LD) -o $(BINS) $(BINS).o $(LDFLAGS) $(LDLIBS) -lgcc $(LIBS) -L/export/data_1/rbradley/satellite/Sat1/fftw-3.0.1/.libs -L/usr/lib -lpci_dask -lpthread conio.o

$(BINS).o : $(BINS).c
	$(CC) -c $(CFLAGS) $(BINS).c 

conio.o: /usr/local/pci-dask_427/samples/conio/conio.c
	gcc -c -I/usr/local/pci-dask_427/include /usr/local/pci-dask_427/samples/conio/conio.c

clean:
	-rm -f $(BINS).o 

clear: 
	-rm -f $(BINS) 


