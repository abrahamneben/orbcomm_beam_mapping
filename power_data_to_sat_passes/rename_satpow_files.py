# rename satpower20130425.1 to satpower20130425132451.dat

import os

d= 'zenith3'
fnames = os.listdir(d)

for fname in fnames:
	f=open(d+'/'+fname,'r')
	f.readline()
	f.readline()
	dstr=f.readline()
	f.close()

	dstrsplit = dstr.split(' ')
	day = dstrsplit[3]
	time = dstrsplit[4].split(':')
	newname = 'satpower201304'+day+''.join(time)+'.dat'

	print 'renaming '+d+'/'+fname+' to '+d+'/'+newname
	os.rename(d+'/'+fname,d+'/'+newname)
	

