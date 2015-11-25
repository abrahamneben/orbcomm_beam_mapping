#!/Users/abrahamn/bin/py

import sys
from datetime import datetime
import calendar
import commands


oldmapfname = sys.argv[1]
tle_prefix = sys.argv[2] # if the tle files are orbcomm_20131106113043_1.tle and orbcomm_20131106113043_2.tle, then put "orbcomm_20131106113043"

newmapfname=oldmapfname+'_fixed_sat_positions'

oldmapfile=open(oldmapfname,'r')
newmapfile=open(newmapfname,'w')

oldmapfile_numlines = int(commands.getoutput('wc -l '+oldmapfname).split()[0])
currline=-1

for line in oldmapfile:
	currline += 1
	ls = line.split()
	if len(ls) != 19:
		newmapfile.write(line)
		continue

	dt = datetime.strptime(ls[17]+' '+ls[18],"%m/%d/%Y %H:%M:%S")
	dt_unix = str(calendar.timegm(dt.utctimetuple()))

	satnum = int(ls[14])
	satnumstr = '%02d'%(satnum)

	if satnum < 30:
		tlefname = tle_prefix+'_1.tle'
	else:
		tlefname = tle_prefix+'_2.tle'

	predict_out = commands.getoutput('predict -t '+tlefname+' -f FM'+satnumstr+' '+dt_unix).split()
	#print predict_out

	ls[0] = str(90-float(predict_out[4]))
	ls[1] = predict_out[5]

	newmapfile.write(' '.join(ls)+'\n')

	if currline%5000 == 0:
		print str(currline/float(oldmapfile_numlines)*100)+'%'

oldmapfile.close()
newmapfile.close()