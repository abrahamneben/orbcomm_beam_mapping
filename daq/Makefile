#Makefile for HP3325Acontrol

CC = gcc

IFLAGS=  -I. -I/usr/local/include

#CFLAGS =  -L/usr/local/lib
 
#LIBS = -lgpibapi
LIBS = -ldl

#BINS = HP3325Asetup
BINS = HP8656Bsetup

all: $(BINS) clean


$(BINS): $(BINS).c
	$(CC) -o $(BINS) $(BINS).c /usr/local/natinst/ni4882/lib/cib.o $(LIBS) $(IFLAGS)

clean:
	-rm -f $(BINS).o 

clear: 
	-rm -f $(BINS) 
