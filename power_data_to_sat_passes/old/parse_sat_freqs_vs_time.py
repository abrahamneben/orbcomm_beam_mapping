#!/usr/bin/python

# 
# parse_sat_freqs_vs_time.py
#

# Look for all the satpass files in the specified directory, and parse them into relative and absolute power maps, add model data

# 1: MWA E/W
# 2: ref E/W
# 3: MWA N/S
# 4: ref N/S

# These sat pass data files look like this:
# 08/24/2012 07:59:40  6 2012.647487950279    76742 222.59  GB 290.950 -0.000 3243.14  80 102 0.424921 0.086474 0.382924 0.080363
#  0.000915 0.000892 0.000830 0.000864 0.000869 0.000810 0.000835
#  0.000145 0.000140 0.000154 0.000171 0.000166 0.000197 0.000189
#  0.000796 0.000764 0.000873 0.000808 0.000795 0.000712 0.000713
#  0.000140 0.000144 0.000151 0.000163 0.000138 0.000170 0.000157
# 08/24/2012 07:59:40  6 2012.647487950279    76742 222.59  GB 290.950 -0.000 3243.14  80 102 0.426212 0.088586 0.383139 0.078939
#  0.000909 0.000950 0.000872 0.000763 0.000794 0.000858 0.000907
#  0.000152 0.000132 0.000147 0.000136 0.000139 0.000166 0.000142
#  0.000828 0.000795 0.000791 0.000713 0.000844 0.000847 0.000898
#  0.000130 0.000117 0.000126 0.000128 0.000106 0.000124 0.000123

# As of 9/13/2012, the new sat pass data files include 4 extra numbers on each aq header line. They are the sums of the amplitudes of ALL the 512 FFT bins for than input (spanning 137--138 MHz)

# The 12th col is the fftbincenter

satindex = 3-1
fftbincenterindex = 12-1

from numpy import *
	

from os import listdir,system
import sys


#satpassdir = "/export/data_2/aneben/compositeZ02/"
satpassdir = "/export/data_2/aneben/composite20degE/"
satcalanalysisroot = "/export/data_2/aneben/satcalanalysis/"
allfilenames = listdir(satpassdir)
satpassdatafilenames = filter(lambda k: 'withtimes' in k, allfilenames)

# parse sat pass data files
for satpassdatafilename in satpassdatafilenames:

	print satpassdatafilename

	satpassdatafile = open(satpassdir+satpassdatafilename,'r')
	satpassdata = satpassdatafile.readlines()
	satpassdatafile.close()

	freqfile = open(satpassdir+satpassdatafilename +'_freqs.tsv','w')
	
	num_passes = len(satpassdata)/5
	
	for pass_index in range(num_passes):
		if pass_index % 5 == 0:
		#if True:
			
			aqheader = satpassdata[5*pass_index].split()
			#satfmnum = aqheader[2]
			az,el = map(float,aqheader[7:9])
			datetime =  ' '.join(aqheader[0:2])
			satfreq = float(aqheader[fftbincenterindex])/512.+137

			freqfile.write(datetime + '\t' + str(satfreq) + '\t' + str(az) + '\t' + str(el) + '\n')


	freqfile.close()





