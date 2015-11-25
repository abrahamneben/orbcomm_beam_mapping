#!/usr/bin/python

# Read in a mapfile, break into passes, put high SNR passes into a new mapfile,
# and also add the polarized ref. ant beams to that new mapfile

import numpy as np
from numpy import log10,median
import matplotlib
import sys
import commands


def makemodelarr(fname,colnum): # colnum: 2 is P_abs=P_theta+P_phi, 3 is P_theta, 4 is P_phi
	# 1st dim is zenith angle 0:89, 2nd dim is az 0:359.9, in steps of 1 deg
	# zenith angle is incremented first
	arr = np.zeros(90*360,dtype=float).reshape(90,360)
	f = open(fname,'r')
	ftext = f.readlines()
	fdata = [map(float,line.split()) for line in ftext]
	f.close()
	for line in fdata:
		arr[int(line[0])][int(line[1])] = line[colnum]
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

satcalanalysisroot = "/Users/abrahamn/sat_cal/satcalanalysis/"
oldrefmodelarrNS = makemodelarr(satcalanalysisroot+'refModel/ff137_5_xpol+el.txt',2)
newrefmodelarrNS = makemodelarr(satcalanalysisroot+'refModel/new_ref_dipole_model_137_31july2015+el.txt',2)
#refmodelarrEWtheta = makemodelarr(satcalanalysisroot+'refModel/ff137_5_ypol+el.txt',3) # y <=> EW and x <=> NS for these files that Rich made
#refmodelarrEWphi = makemodelarr(satcalanalysisroot+'refModel/ff137_5_ypol+el.txt',4)
#refmodelarrNStheta = makemodelarr(satcalanalysisroot+'refModel/ff137_5_xpol+el.txt',3)
#refmodelarrNSphi = makemodelarr(satcalanalysisroot+'refModel/ff137_5_xpol+el.txt',4)

#label = 'null4'
label = sys.argv[1]
print 'processing '+label
mapfilename = 'mapfile'+label
newmapfilename = mapfilename+'_snrfilt_add_old_new_refmodel'
datadir='/Users/abrahamn/data/21cm/hera/2015/jul13/'+label+'/'

print 'reading ' + mapfilename

f=open(datadir+mapfilename,'r')
fd=f.readlines()[19:]
f.close()

### old mapfile
# 1: za (deg)
# 2: az (deg)
# 3: 10*log10(tile EW) = (10*log10 of sum amps over 7 FFT bin band)^2
# 4: 10*log10(ref EW) = (10*log10 of sum amps over 7 FFT bin band)^2
# 5: 10*log10(tile NS) = (10*log10 of sum amps over 7 FFT bin band)^2
# 6: 10*log10(ref NS) = (10*log10 of sum amps over 7 FFT bin band)^2
# 8: ref model EW (dB)
# 10: ref model NS (dB)
# 11: 10*log10(tot pow tileEW) = (10*log10(sum squares of RMS FFT amps across 137--138 MHz band)), this will somewhat underestimate tot power in receiver due to finite bandwidths of coherent sat signals
# 12: 10*log10(tot pow refEW)
# 13: 10*log10(tot pow tileNS)
# 14: 10*log10(tot pow refNS)
# 15: orbcomm sat FM #
# 16: pass number
# 17: hours_since_start
# 18: date time string (UTC)

# find pass boundaries
pass_start_indices = [0]
num_records = len(fd)
for recordi in range(num_records):
#	print fd[recordi].split()
	hours = float(fd[recordi].split()[15-1])
	sat = fd[recordi].split()[13-1]
	if recordi > 0 and (abs(hours-hours_old)>.5 or sat!=sat_old):
		pass_start_indices.append(recordi)
		#print 'recordi='+str(recordi) + '\tsat='+str(sat)+'\thours='+str(hours)
	hours_old = hours
	sat_old = sat
pass_start_indices.append(num_records-1)

def filter_by_snr(tileew,refew,tilens,refns,tileskyew,refskyew,tileskyns,refskyns,refewtot,tileewtot,refnstot,tilenstot): # all log pows
	#minsnr = 12
	minsnr = 15
	maxtotpow = -10

	high_snr =  (tileew-tileskyew > minsnr) & (refew-refskyew > minsnr) & (tilens-tileskyns > minsnr) & (refns-refskyns > minsnr)
	low_tot_pow = (tileewtot < maxtotpow) & (refewtot < maxtotpow) & (tilenstot < maxtotpow) & (refnstot < maxtotpow)
	good = high_snr & low_tot_pow

	near_moving_median = np.zeros(len(tileew),dtype=bool)
	maxdistfrommedian = 1
	n0=40
	for i in range(n0/2,len(tileew)-n0/2):
		if good[i] == False: continue

		unflagged = np.where(good[i-n0/2:i+n0/2])[0]

		tileewwind0=tileew[i-n0/2:i+n0/2]
		refewwind0=refew[i-n0/2:i+n0/2]
		tilenswind0=tilens[i-n0/2:i+n0/2]
		refnswind0=refns[i-n0/2:i+n0/2]
		tileewwind = tileewwind0[unflagged]
		refewwind = refewwind0[unflagged]
		tilenswind = tilenswind0[unflagged]
		refnswind = refnswind0[unflagged]


		tileew_devfrommedian = np.abs(tileew[i]-np.median(tileewwind))
		refew_devfrommedian = np.abs(refew[i]-np.median(refewwind))
		tilens_devfrommedian = np.abs(tilens[i]-np.median(tilenswind))
		refns_devfrommedian = np.abs(refns[i]-np.median(refnswind))

		# BEWARE than '&' is not the same as 'and' for python objects, but numpy overloads '&' to make it the same as 'and' for numpy objects
		if (tileew_devfrommedian<maxdistfrommedian)and(refew_devfrommedian<maxdistfrommedian)and(tilens_devfrommedian<maxdistfrommedian)and(refns_devfrommedian<maxdistfrommedian):
			near_moving_median[i] = True

#		print [tileew[i],tileew_devfrommedian]

	x=np.where(high_snr & low_tot_pow & near_moving_median)[0]
	return x


# def filter_by_snr(tileew,refew,tilens,refns,tileskyew,refskyew,tileskyns,refskyns,refewtot,tileewtot,refnstot,tilenstot): # all log pows
# 	indices = np.zeros(len(tileew),dtype=int)
# 	num_added = 0

# 	for i in range(len(tileew)):
# 		if (tileew[i]-tileskyew > 10) and (refew[i]-refskyew > 10) and (tilens[i]-tileskyns >10) and (refns[i]-refskyns >10):
# 			indices[num_added] = i
# 			num_added += 1

# 	x=indices[0:num_added]
# 	print x

# 	return x

num_passes = len(pass_start_indices)-1

za_allpasses = np.array([],dtype=float)
az_allpasses = np.array([],dtype=float)
logtileEWsub_allpasses = np.array([],dtype=float)
logrefEWsub_allpasses = np.array([],dtype=float)
logtileNSsub_allpasses = np.array([],dtype=float)
logrefNSsub_allpasses = np.array([],dtype=float)
logtileEWtot_allpasses = np.array([],dtype=float)
logrefEWtot_allpasses = np.array([],dtype=float)
logtileNStot_allpasses = np.array([],dtype=float)
logrefNStot_allpasses = np.array([],dtype=float)
#logrefmodelEWtheta_allpasses = np.array([],dtype=float)
#logrefmodelEWphi_allpasses = np.array([],dtype=float)
#logrefmodelNStheta_allpasses = np.array([],dtype=float)
#logrefmodelNSphi_allpasses = np.array([],dtype=float)
logoldrefmodelEW_allpasses = np.array([],dtype=float)
logoldrefmodelNS_allpasses = np.array([],dtype=float)
lognewrefmodelEW_allpasses = np.array([],dtype=float)
lognewrefmodelNS_allpasses = np.array([],dtype=float)
satnums_allpasses = np.array([],dtype=float)
passnums_allpasses = np.array([],dtype=float)
hours_since_start_all_passes = np.array([],dtype=float)
dtstr_all_passes = np.array([],dtype=long)

print 'found ' + str(num_passes) + ' passes in '+mapfilename
for passi in range(num_passes):

#	if passi==50:break

	if passi%15==0: print float(passi)/len(pass_start_indices)*100

	passdata = np.array([l.split() for l in fd[pass_start_indices[passi]:pass_start_indices[passi+1]]])

	#print passdata
	satnums   = np.array(passdata[:,13-1],dtype=float)
	passnums  = np.array(passdata[:,14-1],dtype=float)
	hours_since_start = np.array(passdata[:,15-1],dtype=float)
	datetimestrs_raw = np.array(passdata[:,(16-1):(18-1)],dtype=object)
	datetimestrs = np.array(['/'.join(s).replace('/','').replace(':','') for s in datetimestrs_raw],dtype=long) #MMDDYYYYHHmmss

#	if not (satnums[0]==32 and passnums[0]==71817): continue

	za = np.array(passdata[:,1-1],dtype=float)
	az = np.array(passdata[:,2-1],dtype=float)

	logtileEW = np.array(passdata[:,3-1],dtype=float)
	logrefEW  = np.array(passdata[:,4-1],dtype=float)
	logtileNS = np.array(passdata[:,5-1],dtype=float)
	logrefNS  = np.array(passdata[:,6-1],dtype=float)

	logtileEWtot = np.array(passdata[:,9-1],dtype=float)
	logrefEWtot  = np.array(passdata[:,10-1],dtype=float)
	logtileNStot = np.array(passdata[:,11-1],dtype=float)
	logrefNStot  = np.array(passdata[:,12-1],dtype=float)

	logtileEWsky = min(median(logtileEW[0:10]),median(logtileEW[-10:-1]))
	logrefEWsky = min(median(logrefEW[0:10]),median(logrefEW[-10:-1]))
	logtileNSsky = min(median(logtileNS[0:10]),median(logtileNS[-10:-1]))
	logrefNSsky = min(median(logrefNS[0:10]),median(logrefNS[-10:-1]))

	g = filter_by_snr(logtileEW,logrefEW,logtileNS,logrefNS,logtileEWsky,logrefEWsky,logtileNSsky,logrefNSsky,logtileEWtot,logrefEWtot,logtileNStot,logrefNStot)

	if len(g)<20: continue

	logtileEWsub = 10*log10(10**(.1*logtileEW[g]) -   10**(.1*logtileEWsky))
	logrefEWsub  = 10*log10(10**(.1*logrefEW[g]) -    10**(.1*logrefEWsky))
	logtileNSsub = 10*log10(10**(.1*logtileNS[g]) -   10**(.1*logtileNSsky))
	logrefNSsub  = 10*log10(10**(.1*logrefNS[g]) - 10**(.1*logrefNSsky))

	logoldrefmodelEW = [interpolatemodel(za[i],(az[i]+90)%360,oldrefmodelarrNS) for i in g]
	logoldrefmodelNS = [interpolatemodel(za[i],az[i],oldrefmodelarrNS) for i in g]
	lognewrefmodelEW = [interpolatemodel(za[i],(az[i]+90)%360,newrefmodelarrNS) for i in g]
	lognewrefmodelNS = [interpolatemodel(za[i],az[i],newrefmodelarrNS) for i in g]
	#logrefmodelEWtheta = [interpolatemodel(za[i],az[i],refmodelarrEWtheta) for i in g]
	#logrefmodelEWphi = [interpolatemodel(za[i],az[i],refmodelarrEWphi) for i in g]
	#logrefmodelNStheta = [interpolatemodel(za[i],az[i],refmodelarrNStheta) for i in g]
	#logrefmodelNSphi = [interpolatemodel(za[i],az[i],refmodelarrNSphi) for i in g]

	za_allpasses = np.append(za_allpasses,za[g])
	az_allpasses = np.append(az_allpasses,az[g])
	logtileEWsub_allpasses = np.append(logtileEWsub_allpasses,logtileEWsub)
	logrefEWsub_allpasses = np.append(logrefEWsub_allpasses,logrefEWsub)
	logtileNSsub_allpasses = np.append(logtileNSsub_allpasses,logtileNSsub)
	logrefNSsub_allpasses = np.append(logrefNSsub_allpasses,logrefNSsub)

	logoldrefmodelEW_allpasses = np.append(logoldrefmodelEW_allpasses,logoldrefmodelEW)
	logoldrefmodelNS_allpasses = np.append(logoldrefmodelNS_allpasses,logoldrefmodelNS)
	lognewrefmodelEW_allpasses = np.append(lognewrefmodelEW_allpasses,lognewrefmodelEW)
	lognewrefmodelNS_allpasses = np.append(lognewrefmodelNS_allpasses,lognewrefmodelNS)
	#logrefmodelEWtheta_allpasses = np.append(logrefmodelEWtheta_allpasses,logrefmodelEWtheta)
	#logrefmodelEWphi_allpasses = np.append(logrefmodelEWphi_allpasses,logrefmodelEWphi)
	#logrefmodelNStheta_allpasses = np.append(logrefmodelNStheta_allpasses,logrefmodelNStheta)
	#logrefmodelNSphi_allpasses = np.append(logrefmodelNSphi_allpasses,logrefmodelNSphi)
	satnums_allpasses = np.append(satnums_allpasses,satnums[g])
	passnums_allpasses = np.append(passnums_allpasses,passnums[g])
	hours_since_start_all_passes = np.append(hours_since_start_all_passes,hours_since_start[g])
	logtileEWtot_allpasses = np.append(logtileEWtot_allpasses,logtileEWtot[g])
	logrefEWtot_allpasses = np.append(logrefEWtot_allpasses,logrefEWtot[g])
	logtileNStot_allpasses = np.append(logtileNStot_allpasses,logtileNStot[g])
	logrefNStot_allpasses = np.append(logrefNStot_allpasses,logrefNStot[g])
	dtstr_all_passes = np.append(dtstr_all_passes,datetimestrs[g])


newmapfileheader = '''
1: za (deg)
2: az (deg)
3: 10*log10(tile EW) = 10*log10(sum amps over 7 FFT bin band)^2 (dB), sky background is subtracted
4: 10*log10(ref EW) = 10*log10(sum amps over 7 FFT bin band)^2 (dB)
5: 10*log10(tile NS) = 10*log10(sum amps over 7 FFT bin band)^2 (dB)
6: 10*log10(ref NS) = 10*log10(sum amps over 7 FFT bin band)^2 (dB)
7: tileEWtot
8: refEWtot
9: tileNStot
10: refNStot
#11: refmodelEWtheta (dB)
#12: refmodelEWphi (dB)
#13: refmodelNStheta (dB)
#14: refmodelNSphi (dB)
11: oldrefmodelEW (dB)
12: oldrefmodelNS (dB)
13: newrefmodelEW (dB)
14: newrefmodelNS (dB)
15: orbcomm sat FM #
16: pass number
17: hours_since_start
18: datetime string MMDDYYYYhhmmss\n'''

#print dtstr_all_passes

print 'writing '+newmapfilename
newmapfiledata =  np.transpose(np.asarray([ za_allpasses, \
	az_allpasses, \
	logtileEWsub_allpasses, \
	logrefEWsub_allpasses, \
	logtileNSsub_allpasses, \
	logrefNSsub_allpasses, \
	logtileEWtot_allpasses, \
	logrefEWtot_allpasses, \
	logtileNStot_allpasses, \
	logrefNStot_allpasses, \
	# logrefmodelEWtheta_allpasses, \
	# logrefmodelEWphi_allpasses, \
	# logrefmodelNStheta_allpasses, \
	# logrefmodelNSphi_allpasses, \
	logoldrefmodelEW_allpasses, \
	logoldrefmodelNS_allpasses, \
	lognewrefmodelEW_allpasses, \
	lognewrefmodelNS_allpasses, \
	satnums_allpasses, \
	passnums_allpasses, \
	hours_since_start_all_passes, \
	dtstr_all_passes]))

#print newmapfiledata.shape

np.savetxt(datadir+newmapfilename, newmapfiledata, delimiter=',',header=newmapfileheader, fmt='%1.2f %1.2f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f %d %d %1.3f %d')




