#!/usr/bin/python

# ./make_listpowerfiles zenith

# 11
# ../compositeE01S00/passinfo
# ../compositeE01S00/passdataforsat
# ../compositeE01S00/noisefile
# /media/disk-1/MWA_Tile/newdata/E01S00/satpower20130413.00
# /media/disk-1/MWA_Tile/newdata/E01S00/satpower20130413.01
# /media/disk-1/MWA_Tile/newdata/E01S00/satpower20130413.02
# /media/disk-1/MWA_Tile/newdata/E01S00/satpower20130413.03

import os
import sys
import commands

label = sys.argv[1]
fname = 'listpowerfiles_'+label
print 'writing '+ fname

if not os.path.exists('../phase4/composite_'+label):
	print 'making directory ../phase4/'+label
	os.makedirs('../phase4/composite_'+label)

# run orbcommscan
# orbcommscan must be run in gdb, otherwise it segfaults
#orbcomfname = commands.getoutput('ls ../phase2/'+label+'/orbcom*')
#print commands.getoutput('./orbcommscan '+orbcomfname)

extdiskroot = '/media/disk-1/MWA_Tile/newdata/'

# write listpowerfiles
f=open(fname,'w')
data_fnames = commands.getoutput('ls '+extdiskroot+label+'/satpower*').split('\n')
print commands.getoutput('cp '+extdiskroot+label+'/orbcom* '+'../phase4/composite_'+label)

f.write(str(len(data_fnames))+'\n')
f.write('../phase4/composite_'+label+'/passinfo'+'\n')
f.write('../phase4/composite_'+label+'/passdataforsat'+'\n')
f.write('../phase4/composite_'+label+'/noisefile'+'\n')

for data_fname in data_fnames:
	f.write(data_fname+'\n')

f.write('\n')
f.close()


