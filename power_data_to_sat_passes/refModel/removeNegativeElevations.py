#!/usr/bin/python

# read the model beampattern files and remove negative zenith angle data

def process(filename):
	f = open(filename+'.txt','r')
	a = f.readlines()[2:]
	f.close()
	
	f2 = open(filename+'+el.txt','w')
	
	for line in a:
		if float(line[0:13]) < 90:
			f2.write(' '.join(line.split())+'\n')
	f2.close()	

#fnames = ['ff137_0_xpol','ff137_0_ypol','ff137_5_xpol','ff137_5_ypol','ff138_0_xpol','ff138_0_ypol']
#fnames=['MWA_tile_zenith_rect_gnd01_01']
fnames=['MWAtile_FF_Zenith_137_5_MHz']

for fname in fnames:
	process(fname)
