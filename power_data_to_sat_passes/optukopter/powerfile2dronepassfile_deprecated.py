#!/usr/bin/python

import sys
import numpy as np
import commands
import datetime
from astropy.time import Time

def compute_dyear(strmonth,date,year,hour,minute,second):
        strmonth2daysuntilmonthstart = {}
        strmonth2daysuntilmonthstart['Jan'] = [0.,1]
        strmonth2daysuntilmonthstart['Feb'] = [31.,2]
        strmonth2daysuntilmonthstart['Mar'] = [59.,3]
        strmonth2daysuntilmonthstart['Apr'] = [90.,4]
        strmonth2daysuntilmonthstart['May'] = [120.,5]
        strmonth2daysuntilmonthstart['Jun'] = [151.,6]
        strmonth2daysuntilmonthstart['Jul'] = [181.,7]
        strmonth2daysuntilmonthstart['Aug'] = [212.,8]
        strmonth2daysuntilmonthstart['Sep'] = [243.,9]
        strmonth2daysuntilmonthstart['Oct'] = [273.,10]
        strmonth2daysuntilmonthstart['Nov'] = [304.,11]
        strmonth2daysuntilmonthstart['Dec'] = [334.,12]
        maccum = strmonth2daysuntilmonthstart[strmonth][0]
        month = strmonth2daysuntilmonthstart[strmonth][1]

        return year+(maccum + date + (hour+(minute/60.+second/3600.))/24.)/365,month

def running_linear_interpolation(gpstimes):
    interp_window_size = 20
    n = len(gpstimes)
    gpstimes_windowedlinearinterp = np.zeros(n)
    numwindows = int(np.ceil((1.*n)/interp_window_size))
    
    for windowi in range(numwindows):
        window = np.array([windowi*interp_window_size,min((windowi+1)*interp_window_size,n-1)])
        
        gpstimeindices = np.arange(window[0],window[1]+1)
        p = np.polyfit(gpstimeindices,gpstimes[gpstimeindices],1)
        gpstimes_windowedlinearinterp[gpstimeindices] = p[1] + p[0]*gpstimeindices
    return gpstimes_windowedlinearinterp

def read_satpower(d,datasetname,flightdatfilename,satfreqbin):
	powerfile = open(d+flightdatfilename+'raw','r')
	print '\nreading '+d+flightdatfilename+'raw'

	dronepassfilename = d+datasetname+'/'+flightdatfilename+'_noninterp'
	print '\nwriting '+dronepassfilename
	dronepassfile = open(dronepassfilename,'w')

	l = powerfile.readline()
	while l != '':
		if "Acquisition" in l:
			acqnum = int(l.split()[1])
			#if acqnum % 100 == 0: print acqnum
		elif 'UT' in l:
			dtobjects = l.split()
			strmonth = dtobjects[2]
			day = int(dtobjects[3])
			hour,minute,second = map(int,dtobjects[4].split(':'))
			year = int(dtobjects[5])
			dyear,month = compute_dyear(strmonth,day,year,hour,minute,second)
			gpstime = Time(datetime.datetime(year,month,day,hour,minute,second),format='datetime',scale='utc').gps
		elif 'CH 1' in l:
			try:
#			print acqnum
				spec = np.array([map(float,powerfile.readline().strip().split()) for i in range(512)])
				satspec = np.array(spec[satfreqbin-3:satfreqbin+3,:])
				dronepassfile.write("%d "%gpstime)
				for i in range(4): dronepassfile.write("%.6f %.6f %.6f %.6f %.6f %.6f "%(satspec[0,i],satspec[1,i],satspec[2,i],satspec[3,i],satspec[4,i],satspec[5,i]))
				dronepassfile.write("\n")
			except:
				print 'error reading acquisition # '+str(acqnum)
		l = powerfile.readline()

	powerfile.close()
	dronepassfile.close()

	# replace gps times with interpolated ones
	dronepassdat = np.genfromtxt(dronepassfilename)
        gpstimes = dronepassdat[:,0]
        gpstimes_windowedlinearinterp = running_linear_interpolation(gpstimes)
        dronepassdat[:,0] = gpstimes_windowedlinearinterp
        np.savetxt(d+datasetname+'/'+flightdatfilename,dronepassdat,fmt='%.3f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f')

if len(sys.argv) != 2:
        print 'usage: powerfiles2dronepassfile.py satpowerflight4.00'
        sys.exit(1)

d = '/export/data_2/rbradley/data/'
flightdatfilename = sys.argv[1]
datasetname = 'optukopter/aug2015'

optukopterfreqMHz = 137.5
satfreqbin = int((optukopterfreqMHz-137.)*512.)

read_satpower(d,datasetname,flightdatfilename,satfreqbin)


