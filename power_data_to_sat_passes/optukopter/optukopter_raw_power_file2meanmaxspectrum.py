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

#analysisroot = '/export/data_1/rbradley/satcalanalysis/'

#label = sys.argv[1]
#antname = sys.argv[2]
label = 'satpowerflight12.00raw'
antname ='tileEW'

if antname == 'tileEW':   antcol=0
elif antname == 'refEW':  antcol=1
elif antname == 'tileNS': antcol=2
elif antname == 'refNS':  antcol=3

#satpowerfilelist = open(analysisroot+'listpowerfiles_'+label)
#satpowerfiles = [name.strip() for name in satpowerfilelist.readlines()[4:-1]]
#satpowerfilelist.close()
satpowerfilepath = '/export/data_2/rbradley/data/'+label

numspectra = 13000
numadded=0
sumspectrum = np.zeros(512)
maxspectrum = np.zeros(512)

print 'loading '+satpowerfilepath
satpowerfile = open(satpowerfilepath)
for i in range(numspectra):
	if i%2000 == 0: print str(i) + '/'+str(numspectra)
	powerspectrum = read_next_spectrum(satpowerfile,antcol)
	
	sumspectrum += powerspectrum
	maxspectrum = np.maximum(maxspectrum,powerspectrum)
	#headers += '\n'+str(numadded)+'\n'+'\n'.join(header.split('\n')[2:-2])
	numadded += 1

satpowerfile.close()

np.savetxt('/export/data_2/rbradley/data/'+label+'_meanpowerspectrum_'+antname+'.txt',10*np.log10(sumspectrum/numadded),fmt='%1.3e')
np.savetxt('/export/data_2/rbradley/data/'+label+'_maxpowerspectrum_'+antname+'.txt',10*np.log10(maxspectrum),fmt='%1.3e')


