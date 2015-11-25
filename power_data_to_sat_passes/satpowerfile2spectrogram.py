#!/users/aneben/python/bin/python

# parse a single column of a satpower file into a spectrogram 
# freqs are colums
# times are rows, say, every few seconds record a power measurement

import sys
import numpy as np

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

	return [header,spectrum]

if len(sys.argv)!=4:
	print 'Usage: ./make_spectrogram [label, eg E01S01] [satpowerfile number] [tileEW/refEW/tileNS/refNS]'
	print 'assumes satpower files are on ext. drive'
	sys.exit(1)

analysisroot = '/export/data_2/aneben/satcalanalysis/'

label = sys.argv[1]
satpowerfilenum = int(sys.argv[2])
antname = sys.argv[3]
if antname == 'tileEW':   antcol=0
elif antname == 'refEW':  antcol=1
elif antname == 'tileNS': antcol=2
elif antname == 'refNS':  antcol=3

satpowerfilelist = open(analysisroot+'listpowerfiles_'+label)
satpowerfiles = [name.strip() for name in satpowerfilelist.readlines()[4:]]
satpowerfilelist.close()

numspectra = 40000
numadded=0
skip=3
spectrogram = np.zeros(shape=(np.ceil(numspectra/float(skip)),512))
satpowerfilename = satpowerfiles[satpowerfilenum]
satpowerfile = open(satpowerfilename)
headers = ''

print 'reading ' + str(numspectra) + ' ' + antname + ' spectra from ' + satpowerfilename
for i in range(numspectra):
	if i%200 == 0: print str(i) + '/'+str(numspectra)
	[header,spectrum] = read_next_spectrum(satpowerfile,antcol)
	
	if i%skip == 0:
		spectrogram[numadded,:] = spectrum
		headers += '\n'+str(numadded)+'\n'+'\n'.join(header.split('\n')[2:-2])
		numadded += 1

satpowerfile.close()

np.savetxt('../phase3/spectrograms/'+label+'_satpower'+str(satpowerfilenum)+'_'+antname+'_every'+str(skip)+'.spectrogram',spectrogram,fmt='%1.2e')

f=open('../phase3/spectrograms/'+label+'_satpower'+str(satpowerfilenum)+'_'+antname+'_every'+str(skip)+'.headers','w')
f.write(headers)
f.close()

