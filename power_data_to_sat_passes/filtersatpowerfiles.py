#!/users/aneben/python/bin/python

import sys
import commands
import numpy as np
import string 

np.set_printoptions(precision=3,linewidth=200)

months={'Jan':'01','Feb':'02','Mar':'03','Apr':'04','May':'05','Jun':'06','Jul':'07','Aug':'08','Sept':'09','Oct':'10','Nov':'11','Dec':'12'}
def make_datetime_numeric(dt):
	dt_elts = dt.split()
	month = months[dt_elts[2]]
	day = dt_elts[3]
	time = ''.join(dt_elts[4].split(':'))
	year = dt_elts[5]

	return year+month+day+time

def read_next_refew_spectrum(f):
        header = ''
        inheader = True

        while inheader:
                nextline = f.readline()
                if len(nextline) == 0:
                        return [[],[]]
                elif nextline == '   CH 1      CH 2      CH 3      CH 4\n':
                        break
                else:
                        header += nextline

        spectrum = np.zeros(512)

	# cols: tileEW=0, refEW=1, tileNS=2, refNS=3
        for i in range(512): spectrum[i] = float(f.readline().split()[1])

        return [header,spectrum]

label = sys.argv[1]

satpowerdir = '/media/disk-1/MWA_Tile/newdata/'+label
satpowerfnames = commands.getoutput('ls '+satpowerdir+'/satpower*').split()

outf = open('../phase3/composite_'+label+'/'+label+'_filteredsatpows.txt','w')

satbins =  np.array([102, 115, 128, 225, 236, 339, 352, 365 ,378, 410])

skip=4
for fname in satpowerfnames:
	f = open(fname)
	print 'reading '+fname
	acq_num = 0

	[header,spect] = read_next_refew_spectrum(f)
	while len(spect) != 0:
		satstrs = header.split('\n')[3:-2]
		allsats = np.zeros(8,dtype=int)
		sats = [int(satstr[2:4]) for satstr in satstrs]
		allsats[0:len(sats)] = sats

		if acq_num%skip == 0:
			datetime = header.split('\n')[2]
			outf.write('\n'+make_datetime_numeric(datetime))
			for i in range(len(satbins)): outf.write(",%1.3f"%(20*np.log10(spect[satbins[i]])))
			outf.write(',')
			outf.write(','.join(map(str,allsats)))
		acq_num += 1

		if acq_num%5000==0: print acq_num/50000.

		[header,spect] = read_next_refew_spectrum(f)	

	f.close()

outf.close()

