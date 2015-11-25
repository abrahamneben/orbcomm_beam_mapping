import numpy as np
import matplotlib
from matplotlib.ticker import MultipleLocator
import sys

matplotlib.use('agg') # for saving to files
import matplotlib.pyplot as plt

rootdir='/Users/abrahamn/satcal/2013/mar17/null2full/'

mapfilename = sys.argv[1]

print 'reading ' + mapfilename

f=open(rootdir+mapfilename,'r')
fd=f.readlines()[17:]
f.close()

make_plots_and_webpage = False

# 1: za (deg)
# 2: az (deg)
# 3: 10*log10(tile EW) = (10*log10 of sum amps over 7 FFT bin band)^2
# 4: 10*log10(ref EW) = (10*log10 of sum amps over 7 FFT bin band)^2
# 5: 10*log10(tile NS) = (10*log10 of sum amps over 7 FFT bin band)^2
# 6: 10*log10(ref NS) = (10*log10 of sum amps over 7 FFT bin band)^2
# 7: ref model EW (dB)
# 8: ref model NS (dB)
# 9: 10*log10(tot pow tileEW) = (10*log10(sum squares of RMS FFT amps across 137--138 MHz band)), this will somewhat underestimate tot power in receiver due to finite bandwidths of coherent sat signals
# 10: 10*log10(tot pow refEW)
# 11: 10*log10(tot pow tileNS)
# 12: 10*log10(tot pow refNS)
# 13: orbcomm sat FM #
# 14: pass number
# 15: hours_since_start
# 16: date time string (UTC)

# find pass boundaries
pass_start_indices = [0]
num_records = len(fd)
for recordi in range(num_records):
	hours = float(fd[recordi].split()[15-1])
	sat = fd[recordi].split()[13-1]
	if recordi > 0 and (abs(hours-hours_old)>.5 or sat!=sat_old):
		pass_start_indices.append(recordi)
	hours_old = hours
	sat_old = sat
pass_start_indices.append(num_records-1)


def filter_by_snr(tile,ref,tilesky,refsky,tiletot,reftot): # all log pows
	indices = np.zeros(len(tile),dtype=int)
	ratios = np.zeros(len(tile))
	num_added = 0

	for i in range(len(tile)):
		#if (tile[i]-tilesky > 10) and (ref[i]-refsky > 10) and (tiletot[i] < -19) and (reftot[i] < -19):
		if (tile[i]-tilesky > minsnr) and (ref[i]-refsky > minsnr):
			tilesub = 10*np.log10(10**(.1*tile[i]) - 10**(.1*tilesky))
			refsub  = 10*np.log10(10**(.1*ref[i])  - 10**(.1*refsky))
			ratios[num_added]  = tilesub - refsub
			indices[num_added] = i
			num_added += 1

	return [indices[0:num_added],ratios[0:num_added]]

def moving_avg_and_sd(d,per_sec,hours_since_start):

	if len(d)==0: return [[],[]]

	dt = (hours_since_start[-1]-hours_since_start[0])/len(hours_since_start)*3600

	# if dt>1:
	# 	for i in range(len(hours_since_start)):
	# 		print hours_since_start[i]

	if len(d) < 500:
		return [np.zeros(len(d))+np.mean(d),np.zeros(len(d))+np.std(d)]

	per = int(per_sec/dt)

	#print str(len(d))+' samples\tdt = '+str(dt)+'\tper = '+str(per)

	moving_sd = np.zeros(len(d))
	moving_avg = np.zeros(len(d))
	for i in range(per/2,len(d)-per/2):
		moving_sd[i] = np.std( d[(i-per/2):(i+per/2)] )
		moving_avg[i] = np.mean( d[(i-per/2):(i+per/2)] )

	moving_sd[0:per/2] = moving_sd[per/2]
	moving_sd[ (len(d)-per/2):len(d) ] = moving_sd[len(d)-per/2-1]
	moving_avg[0:per/2] = moving_avg[per/2]
	moving_avg[ (len(d)-per/2):len(d) ] = moving_avg[len(d)-per/2-1]

	return [moving_avg,moving_sd]


offset = -1.5
moving_stat_period_sec = 15
minsnr = 20

passplotfilenames = []

pass_start_hours = np.zeros(len(pass_start_indices),dtype=float)
logtileEWskys    = np.zeros(len(pass_start_indices),dtype=float)
logrefEWskys     = np.zeros(len(pass_start_indices),dtype=float)
logtileNSskys    = np.zeros(len(pass_start_indices),dtype=float)
logrefNSskys     = np.zeros(len(pass_start_indices),dtype=float)

tilebeamEW_allpasses = np.array([],dtype=float)
tilebeamNS_allpasses = np.array([],dtype=float)
tilemodbeamEW_allpasses = np.array([],dtype=float)
tilemodbeamNS_allpasses = np.array([],dtype=float)
hours_since_startEW_allpasses = np.array([],dtype=float)
hours_since_startNS_allpasses = np.array([],dtype=float)
zaEW_allpasses = np.array([],dtype=float)
azEW_allpasses = np.array([],dtype=float)
zaNS_allpasses = np.array([],dtype=float)
azNS_allpasses = np.array([],dtype=float)
beamOverModelEWMovingSD_allpasses = np.array([],dtype=float)
beamOverModelNSMovingSD_allpasses = np.array([],dtype=float)
beamOverModelEWMovingAvg_allpasses = np.array([],dtype=float)
beamOverModelNSMovingAvg_allpasses = np.array([],dtype=float)

if make_plots_and_webpage:
	f=open('Null2_'+mapfilename+'.php','w')
	f.write("<?php require('../access.php');?><html><head><title>"+mapfilename+"</title></head><body><h1>"+mapfilename+"</h1>")
	f.write('<img src=\"'+mapfilename+'_plots/skys.png\"/><br/>\n')

for passi in range(len(pass_start_indices)-1):

	#if passi>10: continue

	if passi%15==0: print float(passi)/len(pass_start_indices)*100

	passdata = np.array([l.split() for l in fd[pass_start_indices[passi]:pass_start_indices[passi+1]]])

	satnum   = passdata[0,13-1]
	passnums  = np.unique(passdata[:,14-1])
	passes_str = ','.join(passnums)
	dt_start = ' '.join(passdata[0,16-1:18-1])
	dt_end   = ' '.join(passdata[-1,16-1:18-1])

	za = np.array(passdata[:,1-1],dtype=float)
	az = np.array(passdata[:,2-1],dtype=float)

	logtileEW = np.array(passdata[:,3-1],dtype=float)
	logrefEW  = np.array(passdata[:,4-1],dtype=float)
	logtileNS = np.array(passdata[:,5-1],dtype=float)
	logrefNS  = np.array(passdata[:,6-1],dtype=float)

	logtileEWskys[passi] = min(min(logtileEW[0:10]),min(logtileEW[-10:-1]))
	logrefEWskys[passi] = min(min(logrefEW[0:10]),min(logrefEW[-10:-1]))
	logtileNSskys[passi] = min(min(logtileNS[0:10]),min(logtileNS[-10:-1]))
	logrefNSskys[passi] = min(min(logrefNS[0:10]),min(logrefNS[-10:-1]))

	logtileEWtot = np.array(passdata[:,9-1],dtype=float)
	logrefEWtot  = np.array(passdata[:,10-1],dtype=float)
	logtileNStot = np.array(passdata[:,11-1],dtype=float)
	logrefNStot  = np.array(passdata[:,12-1],dtype=float)

	logrefEWmodel  = np.array(passdata[:,7-1],dtype=float)
	logrefNSmodel  = np.array(passdata[:,8-1],dtype=float)

	[indicesEW,logratioEWsub] = filter_by_snr(logtileEW,logrefEW,logtileEWskys[passi],logrefEWskys[passi],logtileEWtot,logrefEWtot)
	[indicesNS,logratioNSsub] = filter_by_snr(logtileNS,logrefNS,logtileNSskys[passi],logrefNSskys[passi],logtileNStot,logrefNStot)

	logtileEWbeamsub = logratioEWsub + logrefEWmodel[indicesEW]+offset
	logtileNSbeamsub = logratioNSsub + logrefNSmodel[indicesNS]+offset
	logtileEWbeam = (logtileEW-logrefEW) + logrefEWmodel+offset
	logtileNSbeam = (logtileNS-logrefNS) + logrefNSmodel+offset

	hours_since_start = np.array(passdata[:,15-1],dtype=float)
	pass_start_hours[passi] = hours_since_start[0]

	tilebeamEW_allpasses = np.append(tilebeamEW_allpasses,logtileEWbeamsub)
	tilebeamNS_allpasses = np.append(tilebeamNS_allpasses,logtileNSbeamsub)
	tilemodbeamEW_allpasses = np.append(tilemodbeamEW_allpasses,logrefEWmodel[indicesEW])
	tilemodbeamNS_allpasses = np.append(tilemodbeamNS_allpasses,logrefNSmodel[indicesNS])
	hours_since_startEW_allpasses = np.append(hours_since_startEW_allpasses,hours_since_start[indicesEW])
	hours_since_startNS_allpasses = np.append(hours_since_startNS_allpasses,hours_since_start[indicesNS])
	zaEW_allpasses = np.append(zaEW_allpasses,za[indicesEW])
	azEW_allpasses = np.append(azEW_allpasses,az[indicesEW])
	zaNS_allpasses = np.append(zaNS_allpasses,za[indicesNS])
	azNS_allpasses = np.append(azNS_allpasses,az[indicesNS])

	beamOverModelEW = 10**(.1*logtileEWbeamsub-.1*logrefEWmodel[indicesEW])
	beamOverModelNS = 10**(.1*logtileNSbeamsub-.1*logrefNSmodel[indicesNS])

	[beamOverModelEWMovingAvg,beamOverModelEWMovingSD] = moving_avg_and_sd(beamOverModelEW,moving_stat_period_sec,hours_since_start[indicesEW])
	[beamOverModelNSMovingAvg,beamOverModelNSMovingSD] = moving_avg_and_sd(beamOverModelNS,moving_stat_period_sec,hours_since_start[indicesNS])

	beamOverModelEWMovingSD_allpasses = np.append(beamOverModelEWMovingSD_allpasses,beamOverModelEWMovingSD)
	beamOverModelNSMovingSD_allpasses = np.append(beamOverModelNSMovingSD_allpasses,beamOverModelNSMovingSD)
	beamOverModelEWMovingAvg_allpasses = np.append(beamOverModelEWMovingAvg_allpasses,beamOverModelEWMovingAvg)
	beamOverModelNSMovingAvg_allpasses = np.append(beamOverModelNSMovingAvg_allpasses,beamOverModelNSMovingAvg)


	if make_plots_and_webpage:

		plt.clf()
		fig = plt.gcf()
		fig.set_size_inches((60,4))

		plt.subplot(161)
		# plt.subplot(321)
		plt.plot(hours_since_start,logtileEW, '.', label='tileEW', markersize=2)
		plt.plot(hours_since_start,logrefEW, '.', label='refEW', markersize=2)
		plt.plot(hours_since_start,logtileNS, '.', label='tileNS', markersize=2)
		plt.plot(hours_since_start,logrefNS, '.', label='refNS',markersize=2)
		plt.plot(hours_since_start,np.ones(len(hours_since_start))+logtileEWskys[passi],color='black')
		plt.plot(hours_since_start,np.ones(len(hours_since_start))+logrefEWskys[passi],color='black')
		plt.plot(hours_since_start,np.ones(len(hours_since_start))+logtileNSskys[passi],color='black')
		plt.plot(hours_since_start,np.ones(len(hours_since_start))+logrefNSskys[passi],color='black')
		plt.grid(True)
		plt.legend(loc='upper right')
		plt.xlim([hours_since_start[0],hours_since_start[-1]])
		plt.ylim([-70,30])
		plt.title('chan pows')
		#plt.title('tile and ref pows at this sat freq')
		plt.ylabel('dB')

		plt.subplot(162)
		# plt.subplot(322)
		plt.plot(hours_since_start,logtileEWtot, '.', label='tileEWtot', markersize=2)
		plt.plot(hours_since_start,logrefEWtot, '.', label='refEWtot', markersize=2)
		plt.plot(hours_since_start,logtileNStot, '.', label='tileEWtot', markersize=2)
		plt.plot(hours_since_start,logrefNStot, '.', label='refEWtot', markersize=2)
		plt.xlim([hours_since_start[0],hours_since_start[-1]])
		plt.title('tot pows')
		#plt.title('tile and ref tot pow over all freqs')
		plt.ylabel('dB')
		plt.grid(True)
		plt.ylim([-60,0])
		#plt.legend(loc='upper right')

		plt.subplot(163)
		# plt.subplot(323)
		plt.plot(hours_since_start,logtileEWbeam, '.', label='tileEWbeam', markersize=2)
		plt.plot(hours_since_start,logtileNSbeam, '.', label='tileNSbeam', markersize=2)
		plt.plot(hours_since_start,logrefEWmodel)
		plt.plot(hours_since_start,logrefNSmodel)
		plt.xlim([hours_since_start[0],hours_since_start[-1]])
		plt.ylabel('dB')
		plt.ylim([-40,10])
		plt.title('measured tile beam')
		plt.grid(True)
		#plt.legend(loc='upper right')

		plt.subplot(164)
		#plt.subplot(324)
		plt.plot(hours_since_start[indicesEW],logtileEWbeamsub, '.', markersize=2,label='tileEWbeam')
		plt.plot(hours_since_start[indicesNS],logtileNSbeamsub, '.', markersize=2,label='tileNSbeam')
		plt.plot(hours_since_start,logrefEWmodel)
		plt.plot(hours_since_start,logrefNSmodel)
		plt.xlim([hours_since_start[0],hours_since_start[-1]])
		plt.title('sub sky, totpow & SNR cutoffs')
		plt.legend(loc='lower right')
		plt.ylabel('dB')
		plt.grid(True)
		plt.ylim([-40,10])

		ax=plt.subplot(165)
		#plt.subplot(324)
		plt.plot(hours_since_start[indicesEW],beamOverModelEW,label='EW')
		plt.plot(hours_since_start[indicesNS],beamOverModelNS,label='NS')
		plt.xlim([hours_since_start[0],hours_since_start[-1]])
		plt.title('beam/model')
		ax.yaxis.set_major_locator(MultipleLocator(0.5))
		ax.yaxis.set_minor_locator(MultipleLocator(0.1))

		ax.xaxis.grid(True)
		ax.yaxis.grid(True,'major',linestyle='-')
		ax.yaxis.grid(True,'minor',linestyle=':')

		plt.legend(loc='lower right')
		plt.ylabel('fraction')
		plt.ylim([0,2])

		plt.subplot(166,polar=True)
		plt.plot(az*np.pi/180.,za, '.', markersize=2)
		plt.grid(True)
		plt.ylim([0,90])

		note='pass: %i, sat %s, passes: %s, %s - %s'%(passi,satnum,passes_str,dt_start,dt_end)
		
		passplotfilename = mapfilename+'_plots/sat%s_passes%s.png'%(satnum,passes_str)
		plt.savefig(passplotfilename,dpi=80)
		f.write('<p>%s<br/><img src=\"%s\"/></p>\n'%(note,passplotfilename))

if make_plots_and_webpage:
	f.write('</body></html>')
	f.close()

	plt.clf()
	fig = plt.gcf()
	fig.set_size_inches((15,5))
	plt.plot(pass_start_hours,logtileEWskys,'.')
	plt.plot(pass_start_hours,logrefEWskys,'.')
	plt.plot(pass_start_hours,logtileNSskys,'.')
	plt.plot(pass_start_hours,logrefNSskys,'.')
	plt.grid(True)
	plt.title('sky noise floor (calculated as min(min of first 10, min of last 10))')
	plt.xlabel('hours_since_start')
	plt.ylabel('dB')
	plt.ylim([-70,-40])
	plt.xlim([np.min(pass_start_hours),np.max(pass_start_hours)])
	plt.savefig(mapfilename+'_plots/skys.png',dpi=80)

aEW =  np.transpose(np.asarray([zaEW_allpasses,azEW_allpasses,tilebeamEW_allpasses,tilemodbeamEW_allpasses,beamOverModelEWMovingAvg_allpasses,beamOverModelEWMovingSD_allpasses,hours_since_startEW_allpasses]))
aNS =  np.transpose(np.asarray([zaNS_allpasses,azNS_allpasses,tilebeamNS_allpasses,tilemodbeamNS_allpasses,beamOverModelNSMovingAvg_allpasses,beamOverModelNSMovingSD_allpasses,hours_since_startNS_allpasses]))

print 'writing '+mapfilename+"_EW.csv"
np.savetxt(mapfilename+"_EW.csv", aEW, delimiter=',',fmt='%2.2f %2.2f %2.3f %2.3f %1.3f %1.3f %3.4f')
print 'writing '+mapfilename+"_NS.csv"
np.savetxt(mapfilename+"_NS.csv", aNS, delimiter=',',fmt='%2.2f %2.2f %2.3f %2.3f %1.3f %1.3f %3.4f')


