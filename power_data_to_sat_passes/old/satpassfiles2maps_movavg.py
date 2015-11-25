#!/usr/bin/python

# 
# satpassfiles2maps_movavg.py
#


# this iteration of the file maintains a moving average with a period of 13 records, and also interpolates the models to non-integer az,za

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


def chan_power(string_amplitudes):
	amps = map(float,string_amplitudes)
	#return sum(amps[3-delta_f_bins:4+delta_f_bins])**2
	return sum(amps)**2

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


from os import listdir
from sys import argv
import templog
import numpy as np


# profile by typing the following at the unix terminal
# $ python -m cProfile -o profile.txt satpassfiles2maps_movavg.py Z02

# then open the python terminal:
# >> import pstats
# >> p = pstats.Stats('profile.txt')
# >> p.sort_stats('time').print_stats(20)


avgperiod = 13 # must be odd number
avgsuffix='_'+'movavg'+str(avgperiod)

mapfilesuffix = argv[1]

#GB
satpassdir = "/export/data_2/aneben/composite" + mapfilesuffix + "/"
satcalanalysisroot = "/export/data_2/aneben/satcalanalysis/"

#mac
#satpassdir = "/Users/abrahamn/satcal/satcalanalysis/"
#satcalanalysisroot = "/Users/abrahamn/satcal/satcalanalysis/"

allfilenames = listdir(satpassdir)
satpassdatafilenames = filter(lambda k: 'passdataforsat' in k, allfilenames)

print 'writing to: ' + satpassdir+'mapfile'+mapfilesuffix+avgsuffix
mapfile = open(satpassdir+'mapfile'+mapfilesuffix+avgsuffix, 'w')


mapfile.write("""1: za (deg)
2: az (deg)
3: logratioEW   (10*log10(tileEW/refEW))
4: logratioNS   (10*log10(tileNS/refNS))
5: logratioEW   movavg13
6: logratioNS   movavg13
7: 10*log10(tile EW) = (10*log10 of sum amps over 7 FFT bin band)^2
8: 10*log10(ref EW) = (10*log10 of sum amps over 7 FFT bin band)^2
9: 10*log10(tile NS) = (10*log10 of sum amps over 7 FFT bin band)^2
10: 10*log10(ref NS) = (10*log10 of sum amps over 7 FFT bin band)^2
11: tile model EW (dB)
12: ref model EW (dB)
13: tile model NS (dB)
14: ref model NS (dB)
15: 10*log10(tot pow tileEW) = (10*log10(sum squares of RMS FFT amps across 137--138 MHz band)), this will somewhat underestimate tot power in receiver due to finite bandwidths of coherent sat signals
16: 10*log10(tot pow refEW)
17: 10*log10(tot pow tileNS)
18: 10*log10(tot pow refNS)
19: orbcomm sat FM #
20: beamformer temp (deg F)
21: pass number
22: hours_since_start
23: date time string (UTC)
-----------------------24 header lines---------------
""")

# load model data
refmodelarrNS = makemodelarr(satcalanalysisroot+'refModel/ff137_5_xpol+el.txt')
refmodelarrEW = makemodelarr(satcalanalysisroot+'refModel/ff137_5_ypol+el.txt')
tilemodelarrNS = makemodelarr(satcalanalysisroot+'tileModel/tileNSanalytic.tsv')
tilemodelarrEW = makemodelarr(satcalanalysisroot+'tileModel/tileEWanalytic.tsv')

tempLog = templog.templog()

# parse sat pass data files
for satpassdatafilename in satpassdatafilenames:

	satnum = int(satpassdatafilename[14:16].strip('_'))

	satpassdatafile = open(satpassdir+satpassdatafilename,'r')
	satpassdata = [l.split() for l in satpassdatafile.readlines()]
	satpassdatafile.close()

	num_records = len(satpassdata)/5
	pass_start_indices = [0]
	
	ratiosEW = np.zeros(num_records)
	ratiosNS = np.zeros(num_records)
	logchanpows = np.zeros(num_records*4).reshape(num_records,4)



	# header cols:
	#             UTC time  sat                    orbit#           az      el     range  chan  fftbincenter    sum squares fft amps
	#  08/24/2012 02:19:59  9 2012.646841673009    76739 297.78  GB 79.900 -0.000 3234.42  80   102           0.000593 0.000019 0.000469 0.000009	


	#print '\tpre-parsing'# records to find pass boundaries and ratios'
	for recordi in range(num_records):

		if recordi > 0 and satpassdata[5*recordi][4] != satpassdata[5*(recordi-1)][4]:
			pass_start_indices.append(recordi)

		tileEW = chan_power(satpassdata[5*recordi+1])
		refEW  = chan_power(satpassdata[5*recordi+2])
		tileNS = chan_power(satpassdata[5*recordi+3])
		refNS  = chan_power(satpassdata[5*recordi+4])

		ratiosEW[recordi] = tileEW/refEW
		ratiosNS[recordi] = tileNS/refNS

		logchanpows[recordi,:] = 10*np.log10([tileEW,refEW,tileNS,refNS])

	pass_start_indices.append(num_records-1)

	print 'parsing '+str(len(pass_start_indices))+' passes from '+satpassdatafilename

	#print '\tprinting to mapfile'
	for passi in range(len(pass_start_indices)-1):

		for recordi in range(pass_start_indices[passi]+(avgperiod-1)/2,pass_start_indices[passi+1]-(avgperiod-1)/2):

			#if recordi%5 != 0: continue

			passnum = satpassdata[5*recordi][4]
			date,time =  satpassdata[5*recordi][0:2]
			#dyear = satpassdata[5*recordi][3]
			logtot1,logtot2,logtot3,logtot4 = 10*np.log10( map(float,satpassdata[5*recordi][12:16]) ) # sum squares RMS FFT amps across 137--138 MHz band
			
			az,el = map(float,satpassdata[5*recordi][7:9])
			za = 90-el
		
			temp,hours_since_start = tempLog.get_temp_for_datetime_str(date,time)

			logratioEWmovavg = 10*np.log10( ratiosEW[recordi-(avgperiod-1)/2:recordi+(avgperiod-1)/2+1].mean() )
			logratioNSmovavg = 10*np.log10( ratiosNS[recordi-(avgperiod-1)/2:recordi+(avgperiod-1)/2+1].mean() )

			logratioNS = 10*np.log10(ratiosNS[recordi])
			logratioEW = 10*np.log10(ratiosEW[recordi])

			logtilemodelEW = interpolatemodel(za,az,tilemodelarrEW)
			logrefmodelEW  = interpolatemodel(za,az,refmodelarrEW)
			logtilemodelNS = interpolatemodel(za,az,tilemodelarrNS)
			logrefmodelNS  = interpolatemodel(za,az,refmodelarrNS)

			
			mapfile.write('%1.2f %1.2f %1.2f %1.2f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.1f %1.1f %1.1f %1.1f %d %1.1f %s %1.4f %s\n'%(	za, az, \
									logratioEW,logratioNS,
									logratioEWmovavg,logratioNSmovavg, \
									logchanpows[recordi][0],logchanpows[recordi][1],logchanpows[recordi][2],logchanpows[recordi][3], \
									logtilemodelEW,logrefmodelEW,logtilemodelNS,logrefmodelNS, \
									logtot1,logtot2,logtot3,logtot4, \
									satnum,temp,passnum,hours_since_start,date+' '+time))


mapfile.close()


