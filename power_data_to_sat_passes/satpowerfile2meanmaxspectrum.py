#!/usr/bin/python

# parse a single column of a satpower file into a spectrogram 
# freqs are colums
# times are rows, say, every few seconds record a power measurement

import sys
import numpy as np
import os

def read_next_spectrum(f,colnum): 
	header = ''
	inheader = True

	while inheader:
		nextline = f.readline()
		if len(nextline) == 0:
			return []
		elif nextline == '   CH 1      CH 2      CH 3      CH 4\n':
			break
		else:
			header += nextline

	spectrum = np.zeros(512)

	for i in range(512): spectrum[i] = float(f.readline().split()[colnum])
	powerspectrum = spectrum**2

#	return [header,powerspectrum]
	return powerspectrum

if len(sys.argv)!=3:
	print 'Usage: ./make_spectrogram [label, eg E01S01 [tileEW/refEW/tileNS/refNS]'
	sys.exit(1)

analysisroot = '/export/data_1/rbradley/satcalanalysis/'

label = sys.argv[1]
antname = sys.argv[2]
if antname == 'tileEW':   antcol=0
elif antname == 'refEW':  antcol=1
elif antname == 'tileNS': antcol=2
elif antname == 'refNS':  antcol=3

satpowerfilelist = open(analysisroot+'listpowerfiles_'+label)
satpowerfiles = [name.strip() for name in satpowerfilelist.readlines()[4:-1]]
satpowerfilelist.close()

numspectra = 40000
numadded=0
sumspectrum = np.zeros(512)
maxspectrum = np.zeros(512)

for satpowerfilename in satpowerfiles:
	if os.path.getsize(satpowerfilename)/1.e9 < 1.0:
		print 'skipping incomplete sat power file '+satpowerfilename
		continue

	print 'loading '+satpowerfilename
	satpowerfile = open(satpowerfilename)
	for i in range(numspectra):
		if i%2000 == 0: print str(i) + '/'+str(numspectra)
		powerspectrum = read_next_spectrum(satpowerfile,antcol)
		
		sumspectrum += powerspectrum
		maxspectrum = np.maximum(maxspectrum,powerspectrum)
		#headers += '\n'+str(numadded)+'\n'+'\n'.join(header.split('\n')[2:-2])
		numadded += 1

	satpowerfile.close()

satpowerfile.close()

np.savetxt('/export/data_2/rbradley/data/hera/composite_'+label+'/'+label+'_meanpowerspectrum_'+antname+'.txt',10*np.log10(sumspectrum/numadded),fmt='%1.3e')

np.savetxt('/export/data_2/rbradley/data/hera/composite_'+label+'/'+label+'_maxpowerspectrum_'+antname+'.txt',10*np.log10(maxspectrum),fmt='%1.3e')


