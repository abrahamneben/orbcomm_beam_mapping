#!/usr/bin/python

# 
# satpassfiles2maps.py
#

# Look for all the satpass files in the specified directory, and parse them into relative and absolute power maps, add model data

# 1: MWA E/W
# 2: ref E/W
# 3: MWA N/S
# 4: ref N/S

# These sat pass data files look like this:
#   sat#  date                               el      az

#  7/28/2012 10:30:59 36 2012.573803240741    65996 184.04  GB 293.970 1.360 3141.94 176 225
#  0.001102 0.001055 0.001027 0.001043 0.001052 0.001036 0.000986
#  0.000151 0.000155 0.000149 0.000141 0.000145 0.000139 0.000148
#  0.000788 0.000760 0.000798 0.000759 0.000787 0.000811 0.000754
#  0.000125 0.000135 0.000099 0.000112 0.000122 0.000135 0.000114
#  7/28/2012 10:30:59 36 2012.573803240741    65996 184.05  GB 293.960 1.370 3140.70 176 225
#  0.001168 0.001131 0.001056 0.001031 0.001062 0.001121 0.001080
#  0.000132 0.000141 0.000144 0.000140 0.000159 0.000165 0.000148
#  0.000945 0.000952 0.001004 0.000966 0.001018 0.000997 0.001008
#  0.000139 0.000131 0.000133 0.000150 0.000131 0.000137 0.000135
#    ...

# As of 9/13/2012, the new sat pass data files include 4 extra numbers on each aq header line. They are the sums of the amplitudes of ALL the 512 FFT bins for than input (spanning 137--138 MHz)

from numpy import *

def total_power(string_amplitudes):
	amps = map(float,string_amplitudes.split())
	#return sum(amps[3-delta_f_bins:4+delta_f_bins])**2
	return sum(amps)**2

def makemodelarr(fname):
	# 1st dim is zenith angle 0:89, 2nd dim is az 0:359
	# zenith angle is incremented first
	arr = zeros(90*360,dtype=float).reshape(90,360)
	
	f = open(fname,'r')
	ftext = f.readlines()
	fdata = [map(float,line.split()) for line in ftext]
	f.close()
	
	for line in fdata:
		arr[int(line[0])][int(line[1])] = line[2]
	
	return arr
	

from os import listdir,system
from math import log10
import sys
from numpy import zeros

mapfilesuffix = sys.argv[1]

satpassdir = "/export/data_2/aneben/composite" + mapfilesuffix + "/"
#outputdir = "/export/data_2/aneben/script/"
#satcalanalysisroot = "/Users/abrahamn/sat_cal/satcalanalysis/"
satcalanalysisroot = "/export/data_2/aneben/satcalanalysis/"
#satpassdir = "/Users/abrahamn/sat_cal/aug12/adding time data to mapfiles/"
allfilenames = listdir(satpassdir)
satpassdatafilenames = filter(lambda k: 'withtimes' in k, allfilenames)

print 'writing to: ' + satpassdir+'mapfile'+mapfilesuffix
mapfile = open(satpassdir+'mapfile'+mapfilesuffix, 'w')
mapfile.write('1: az (deg)\n2: el (deg)\n3:tile EW (power)\n4:ref EW (power)\n5:tile NS (power)\n6:ref NS (power)\n7:ref model EW (dB)\n8:ref model NS (dB)\n9:tile model EW (dB)\n10:tile model NS (dB)\n11: MM/DD/YYYY HH:MM:SS UTC\n12:orbcomm sat FM #\n13:tile EW tot pow (sum squares of RMS FFT amps, this will underestimate tot power in receiver due to finite bandwidths of coherent sat signals)\n14:ref EW tot pow\n15:tile NS tot pow\n:16:ref NS tot pow\n-----------------------17 header lines---------------\n')

# load model data
refmodelarrNS = makemodelarr(satcalanalysisroot+'refModel/ff137_0_xpol+el.txt')
refmodelarrEW = makemodelarr(satcalanalysisroot+'refModel/ff137_0_ypol+el.txt')
tilemodelarrNS = makemodelarr(satcalanalysisroot+'tileModel/tileNSanalytic.tsv')
tilemodelarrEW = makemodelarr(satcalanalysisroot+'tileModel/tileEWanalytic.tsv')

# parse sat pass data files
for satpassdatafilename in satpassdatafilenames:

	print satpassdatafilename

	satpassdatafile = open(satpassdir+satpassdatafilename,'r')
	satpassdata = satpassdatafile.readlines()
	satpassdatafile.close()
	
	num_passes = len(satpassdata)/5
	
	curraz_i = -1
	currel_i = -1
	n = -1

	for pass_index in range(num_passes):
	
		aqheader = satpassdata[5*pass_index].split()
		[tot1,tot2,tot3,tot4] = map(float,aqheader[12:16])
		datetime =  ' '.join(aqheader[0:2])
		satfmnum = int(aqheader[2])
		az,el = map(float,aqheader[7:9])
		az_i,el_i = round(az),round(el)

		if az_i == 360:
			az_i = 0
		if el_i <= 1:
			continue

		pow1 = total_power(satpassdata[5*pass_index+1]) # tile EW
		pow2 = total_power(satpassdata[5*pass_index+2]) # ref  EW
		pow3 = total_power(satpassdata[5*pass_index+3]) # tile NS
		pow4 = total_power(satpassdata[5*pass_index+4]) # ref  NS
		
		#print aqheader

		#if :
		if 0 < n < 5 and az_i == curraz_i and el_i == currel_i:
			n += 1
			ratioEW += pow1/pow2
			ratioNS += pow3/pow4
			pows += [pow1,pow2,pow3,pow4]
			totpows += [tot1,tot2,tot3,tot4]
		else:
			if n > 0:
				x='\t'.join(map(str,[az,el,ratioEW/n,ratioNS/n,pows[0]/n,pows[1]/n,pows[2]/n,pows[3]/n,refmodelarrEW[90-el_i][az_i],refmodelarrNS[90-el_i][az_i],tilemodelarrEW[90-el_i][az_i],tilemodelarrNS[90-el_i][az_i],datetime,satfmnum,totpows[0]/n,totpows[1]/n,totpows[2]/n,totpows[3]/n]))+'\n'
				#print x
				mapfile.write(x)
			#print 'new average:'
			n = 1
			ratioEW = pow1/pow2
			ratioNS = pow3/pow4
			curraz_i = az_i
			currel_i = el_i
			pows = [pow1,pow2,pow3,pow4]
			totpows = [tot1,tot2,tot3,tot4]

mapfile.close()



