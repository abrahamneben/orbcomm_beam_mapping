#!/usr/bin/python

import sys
import numpy as np

# from pasinfo file
class SatPass:
	def __init__(self, initstr):
		initvars = initstr.split()
		self.satid = int(initvars[0])
		self.wstart = float(initvars[1])
		self.wstop = float(initvars[2])
		self.chan = int(initvars[3])

# sats as read from the sat power file
class SatInfo:
	def __init__(self,initstr):
		initvars = initstr.split()
		self.satname = initvars[0]
		self.satnum = int(self.satname[2:])
		self.azimuth = float(initvars[1])
		self.elevation = float(initvars[2])
		self.satrange = float(initvars[3])
		self.velocity = float(initvars[4])
		self.meananom = float(initvars[5])
		self.orbitnum = int(initvars[6])

def read_passinfo(passfilename):
	passfile = open(passfilename)
	satpasses = [SatPass(l) for l in passfile.readlines()]
	passfile.close()
	return satpasses	

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

def read_satpower(powerfilename,includepassdata):
	powerfile = open(powerfilename)
	print 'reading '+powerfilename

	l = powerfile.readline()
	while l != '':
		if "Acquisition" in l:
			acqnum = int(l.split()[1])
			#if acqnum % 100 == 0: print acqnum
			satinfos = []
		elif 'UT' in l:
			dtobjects = l.split()
			strmonth = dtobjects[2]
			day = int(dtobjects[3])
			hour,minute,second = map(int,dtobjects[4].split(':'))
			year = int(dtobjects[5])
	
			dyear,month = compute_dyear(strmonth,day,year,hour,minute,second)
		elif 'FM' in l:
			satinfos.append(SatInfo(l))
		elif 'CH 1' in l:
			try:
				#print 'found '+str(len(satinfos))+' satellites'
				spec = np.array([map(float,powerfile.readline().strip().split()) for i in range(512)])

				for satinfo in satinfos:
					for satpass in satpasses:
						if not ( (satpass.wstart < dyear < satpass.wstop) and (satpass.satid == satinfo.satnum) ):
							continue
						centerbin = int(satpass.chan*2.5*512/1000)

						satspec = np.array(spec[centerbin-3:centerbin+4,:])
						totpows = np.sum(satspec,axis=0) # coherent sum

						runningfile = open(includepassdata+str(satinfo.satnum),'a')					
						runningfile.write("%02d/%02d/%4d %02d:%02d:%02d %2d %4.12f %8ld %3.2f GB %3.3f %3.3f %4.2f %3d %3d %2.6f %2.6f %2.6f %2.6f\n"%(month,day,year,hour,minute,second,satinfo.satnum,dyear,satinfo.orbitnum,satinfo.meananom,satinfo.azimuth,satinfo.elevation,satinfo.satrange,satpass.chan,centerbin,totpows[0],totpows[1],totpows[2],totpows[3]))
						for i in range(4):
							runningfile.write('%.6f %.6f %.6f %.6f %.6f %.6f %.6f\n'%(satspec[0,i],satspec[1,i],satspec[2,i],satspec[3,i],satspec[4,i],satspec[5,i],satspec[6,i]))
						runningfile.close()
			except:
				print 'error reading acquisition # '+str(acqnum)
		l = powerfile.readline()

if len(sys.argv) != 2:
	print 'usage: findpassdata4chan.py [listfilename]'
	sys.exit(1)

listname = sys.argv[1]
print 'opening acqfile: ' + listname
listfile = open(listname)
listfilelines = listfile.readlines()

listmax = int(listfilelines[0])
passfilename = listfilelines[1].strip()
includepassdata = listfilelines[2].strip()

print 'reading pass file ' + passfilename

satpasses = read_passinfo(passfilename)

powerfilenames = [l.strip() for l in listfilelines[4:-1]]

for powerfilename in powerfilenames:
	read_satpower(powerfilename,includepassdata)





