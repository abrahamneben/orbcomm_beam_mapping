#!/usr/bin/python

# ./make_listpowerfiles zenith

# 11
# ../data20130413/passinfo
# ../compositeGB0413/passdataforsat
# ../compositeGB0413/noisefile
# ../data20130413/satpower20130413.00
# ../data20130413/satpower20130413.01
# ../data20130413/satpower20130413.02
# ../data20130413/satpower20130413.03

import os
import sys
import commands

label = sys.argv[1]
fname = 'listpowerfiles_'+label
print 'writing '+ fname

if not os.path.exists('../phase3/composite_'+label):
	print 'making directory ../phase3/'+label
	os.makedirs('../phase3/composite_'+label)

# run orbcommscan
# orbcommscan must be run in gdb, otherwise it segfaults
#orbcomfname = commands.getoutput('ls ../phase2/'+label+'/orbcom*')
#print commands.getoutput('./orbcommscan '+orbcomfname)

# write listpowerfiles
f=open(fname,'w')
data_fnames = commands.getoutput('ls ../phase3/'+label+'/satpower*').split('\n')
#os.rename('passinfo','../phase2/zenith/passin3o')

f.write(str(len(data_fnames))+'\n')
f.write('../phase3/'+label+'/passinfo'+'\n')
f.write('../phase3/composite_'+label+'/passdataforsat'+'\n')
f.write('../phase3/composite_'+label+'/noisefile'+'\n')

for data_fname in data_fnames:
	f.write(data_fname+'\n')

f.write('\n')
f.close()



