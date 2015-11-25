#!/usr/bin/python

# 
# satpassfiles2maps_null.py
#


# this iteration of the file interpolates the models to non-integer az,za, but does not moving averaging

# 1: MWA E/W
# 2: ref E/W
# 3: MWA N/S
# 4: ref N/S

# These sat pass data files look like this:
	#             UTC time  sat                    orbit#           az      el     range  chan  fftbincenter    sum squares fft amps

#  08/24/2012 02:19:59  9 2012.646841673009    76739 297.78  GB 79.900 -0.000 3234.42  80   102           0.000593 0.000019 0.000469 0.000009	
#  0.001102 0.001055 0.001027 0.001043 0.001052 0.001036 0.000986
#  0.000151 0.000155 0.000149 0.000141 0.000145 0.000139 0.000148
#  0.000788 0.000760 0.000798 0.000759 0.000787 0.000811 0.000754
#  0.000125 0.000135 0.000099 0.000112 0.000122 0.000135 0.000114
#  08/24/2012 02:19:59  9 2012.646841673009    76739 297.78  GB 79.900 -0.000 3234.42  80   102           0.000593 0.000019 0.000469 0.000009
#  0.001168 0.001131 0.001056 0.001031 0.001062 0.001121 0.001080
#  0.000132 0.000141 0.000144 0.000140 0.000159 0.000165 0.000148
#  0.000945 0.000952 0.001004 0.000966 0.001018 0.000997 0.001008
#  0.000139 0.000131 0.000133 0.000150 0.000131 0.000137 0.000135
#    ...

from os import listdir
from sys import argv
import templog
import numpy as np
from datetime import datetime

def hours_since_time(dt0,date_str,time_str):
	#return datetime.strptime(datetime_str, "%m/%d/%Y %H:%M:%S") # only works in python >2.5
	[month,day,year] = map(int,date_str.split('/'))
	[hour,minute,second] = map(int,time_str.split(':'))
	td = datetime(year,month,day,hour,minute,second)-dt0
	return (td.seconds + td.days * 24 * 3600.)/3600.

def logchan_power(string_amplitudes):
	amps = map(float,string_amplitudes)
	return 10*np.log10(sum(amps)**2)

def makemodelarr(fname):
	# 1st dim is zenith angle 0:89, 2nd dim is az 0:359.9, in steps of 1 deg
	# zenith angle is incremented first
	arr = np.zeros(90*360,dtype=float).reshape(90,360)
	f = open(fname,'r')
	ftext = f.readlines()
	fdata = [map(float,line.split()) for line in ftext]
	f.close()
	for line in fdata:
		arr[int(line[0])][int(line[1])] = line[2]
	return arr

def interpolatemodel(za,az,mod):
	if za > 89: za=89 # the models only go up to za=89, where they are very close to zero anyway
	if az == 360: az=0
	[az1,az2,za1,za2]=[np.floor(az),np.ceil(az)%360,np.floor(za),np.ceil(za)]
	# 	   za1  za   za2
	# az1  a         b
	# az   e   x     f
	# az2  c         d
	a=10**(mod[za1][az1]/10.)
	b=10**(mod[za2][az1]/10.)
	c=10**(mod[za1][az2]/10.)
	d=10**(mod[za2][az2]/10.)
	e=(az-az1)*(c-a)+a
	f=(az-az1)*(d-b)+b
	return 10*np.log10((za-za1)*(f-e)+e)


mapfilesuffix = argv[1]

#GB
satpassdir = "/export/data_2/aneben/composite" + mapfilesuffix + "/"
satcalanalysisroot = "/export/data_2/aneben/satcalanalysis/"

#mac
#satpassdir = "/Users/abrahamn/satcal/satcalanalysis/"
#satcalanalysisroot = "/Users/abrahamn/satcal/satcalanalysis/"

allfilenames = listdir(satpassdir)
satpassdatafilenames = filter(lambda k: 'passdataforsat' in k, allfilenames)

print 'writing to: ' + satpassdir+'mapfile'+mapfilesuffix
mapfile = open(satpassdir+'mapfile'+mapfilesuffix, 'w')

mapfile.write("""1: za (deg)
2: az (deg)
3: 10*log10(tile EW) = (10*log10 of sum amps over 7 FFT bin band)^2
4: 10*log10(ref EW) = (10*log10 of sum amps over 7 FFT bin band)^2
5: 10*log10(tile NS) = (10*log10 of sum amps over 7 FFT bin band)^2
6: 10*log10(ref NS) = (10*log10 of sum amps over 7 FFT bin band)^2
7: ref model EW (dB)
8: ref model NS (dB)
9: 10*log10(tot pow tileEW) = (10*log10(sum squares of RMS FFT amps across 137--138 MHz band)), this will somewhat underestimate tot power in receiver due to finite bandwidths of coherent sat signals
10: 10*log10(tot pow refEW)
11: 10*log10(tot pow tileNS)
12: 10*log10(tot pow refNS)
13: orbcomm sat FM #
14: pass number
15: hours_since_start
16: date time string (UTC)
-----------------------17 header lines---------------
""")

# load model data
refmodelarrNS = makemodelarr(satcalanalysisroot+'refModel/ff137_5_xpol+el.txt')
refmodelarrEW = makemodelarr(satcalanalysisroot+'refModel/ff137_5_ypol+el.txt')

dt_start = datetime(2013,2,26,16,36,0) # Tue Nov 20 01:24:08 2012

# parse sat pass data files
for satpassdatafilename in satpassdatafilenames:

	print 'parsing ' + satpassdatafilename

	satnum = int(satpassdatafilename[14:16].strip('_'))

	satpassdatafile = open(satpassdir+satpassdatafilename,'r')
	satpassdata = [l.split() for l in satpassdatafile.readlines()]
	satpassdatafile.close()

	# header cols:
	#             UTC time  sat                    orbit#           az      el     range  chan  fftbincenter    sum squares fft amps
	#  08/24/2012 02:19:59  9 2012.646841673009    76739 297.78  GB 79.900 -0.000 3234.42  80   102           0.000593 0.000019 0.000469 0.000009	

	for recordi in range(len(satpassdata)/5):

			#if recordi%2 != 0: continue # this is somewhat wasteful of information, perhaps we should do averaging instead

			passnum = int(satpassdata[5*recordi][4])
			date,time =  satpassdata[5*recordi][0:2]
			#dyear = satpassdata[5*recordi][3]
			logtot1,logtot2,logtot3,logtot4 = 10*np.log10( map(float,satpassdata[5*recordi][12:16]) ) # sum squares RMS FFT amps across 137--138 MHz band
			
			az,el = map(float,satpassdata[5*recordi][7:9])
			za = 90-el
		
			hours_since_start = hours_since_time(dt_start,date,time)

			logtileEW = logchan_power(satpassdata[5*recordi+1])
			logrefEW  = logchan_power(satpassdata[5*recordi+2])
			logtileNS = logchan_power(satpassdata[5*recordi+3])
			logrefNS  = logchan_power(satpassdata[5*recordi+4])

			logrefmodelEW  = interpolatemodel(za,az,refmodelarrEW)
			logrefmodelNS  = interpolatemodel(za,az,refmodelarrNS)
			
			mapfile.write('%1.2f %1.2f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %d %d %1.4f %s\n'%(	za, az, \
									logtileEW,logrefEW,logtileNS,logrefNS, \
									logrefmodelEW,logrefmodelNS, \
									logtot1,logtot2,logtot3,logtot4, \
									satnum,passnum,hours_since_start,date+' '+time))


mapfile.close()


