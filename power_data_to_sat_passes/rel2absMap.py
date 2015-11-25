#!/usr/bin/python

# Convert a mapfile with response amplitudes for each pol:
# az      el    tile EW       ref EW       tile NS       ref NS

# 109.770 7.690 3.6108081e-05 1.380625e-06 5.1883209e-05 1.3454224e-05
# 109.640 7.670 2.7825625e-05 1.042441e-06 5.3392249e-05 1.2033961e-05
# 109.550 7.650 3.2353344e-05 1.2544e-06 5.1912025e-05 1.1142244e-05
# 109.460 7.640 3.1629376e-05 8.29921e-07 4.38244e-05 9.665881e-06
# 109.370 7.620 3.26041e-05 9.801e-07 4.4036496e-05 1.0686361e-05
# 109.250 7.600 3.7675044e-05 8.31744e-07 4.6389721e-05 1.1329956e-05

# ...to a mapfile with an absolute power map for each pol


import sys
from numpy import *


def makemodelarr(fname):
	# 1st dim is zenith angle 0:89, 2nd dim is az 0:359
	# zenith angle is incremented first
	arr = arange(90*360).reshape(90,360)
	
	f = open(fname,'r')
	ftext = f.readlines()[2:]
	fdata = [map(float,line.split()) for line in ftext]
	f.close()
	
	for line in fdata:
		arr[int(line[0])][int(line[1])] = line[2]
	
	return arr
	
	

mapfilename = sys.argv[1]

mapfile = open(mapfilename,'r')
mapfiledata = mapfile.readlines()
mapfile.close()

satcalanalysisroot = '/Users/abrahamn/sat_cal/satcalanalysis/'

refmodelarrNS = makemodelarr(satcalanalysisroot+'refModel/ff137_0_xpol+el.txt')
refmodelarrEW = makemodelarr(satcalanalysisroot+'refModel/ff137_0_ypol+el.txt')
tilemodelarrNS = makemodelarr(satcalanalysisroot+'tileModel/tileNS.tsv')
tilemodelarrEW = makemodelarr(satcalanalysisroot+'tileModel/tileEW.tsv')

tileBeamDataAndModelFile = open('mapfile_with_models','w')
tileBeamDataAndModelFile.write('az\tel\ttile EW   ref EW   tileNS   ref NS (lin. power)\t\tref model EW (dB)\tref model NS (dB)\ttile model EW (dB)\ttile model NS (dB)\n')



for line in mapfiledata:

	[az,el,tileEW,refEW,tileNS,refNS] = map(float,line.split())
	az_i,el_i = int(az),int(el)

# 	if el<2:
# 		print line
# 		print [refmodelarrEW[90-el_i][az_i],refmodelarrNS[90-el_i][az_i],tilemodelarr[90-el_i][az_i]]
	
	if el >= 1:
		tileBeamDataAndModelFile.write(str(az)+'\t'+str(el)+'\t')
		tileBeamDataAndModelFile.write(str(tileEW)+'\t'+str(refEW)+'\t'+str(tileNS)+'\t'+str(refNS)+'\t'+str(refmodelarrEW[90-el_i][az_i])+'\t'+str(refmodelarrNS[90-el_i][az_i])+'\t'+str(tilemodelarrEW[90-el_i][az_i])+'\t'+str(tilemodelarrNS[90-el_i][az_i])+'\n')

tileBeamDataAndModelFile.close()
