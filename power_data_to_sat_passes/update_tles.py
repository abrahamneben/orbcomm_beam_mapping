#!/usr/bin/python

## update_tles.py

# this script will download the latest ORBCOMM TLE file from Celestrak, 
# and split them up between 2 files, orbcom1.tle and orbcom2.tle, excluding
# the [-] sats, and will change sat names from "ORBCOMM FM10 [+]        " to "FM10"

# this script is to be run on nekkar

import os
from subprocess import call
import shutil

if os.path.exists('orbcomm.txt'):
	os.rename('orbcomm.txt','orbcomm.txt.old')
if os.path.exists('orbcomm0.tle'):
	os.rename('orbcomm0.tle','orbcomm0.tle.old')
if os.path.exists('orbcomm1.tle'):
	os.rename('orbcomm1.tle','orbcomm1.tle.old')

call(['wget','http://www.celestrak.com/NORAD/elements/orbcomm.txt'])

f=open('orbcomm.txt')
orbcommtle=f.readlines()
f.close()

tle1 = open('orbcomm0.tle','w')
tle2 = open('orbcomm1.tle','w')

#max_num_tle1 = 22
max_num_tle1 = 15
num_added_to_tle1 = 0
num_added_to_tle2 = 0

for sati in range(len(orbcommtle)/3):
	linei = 3*sati

	if '[-]' not in orbcommtle[linei]:
		sattle = orbcommtle[linei].split()[1]+'\n'+orbcommtle[linei+1]+orbcommtle[linei+2]

		if num_added_to_tle1 < max_num_tle1:
			tle1.write(sattle)
			num_added_to_tle1 += 1
		else:
			tle2.write(sattle)
			num_added_to_tle2 +=1

print '='*50+'\n'
print 'wrote ' + str(num_added_to_tle1) + ' orbcomm TLEs to ' + '"orbcomm0.tle"'
print 'wrote ' + str(num_added_to_tle2) + ' orbcomm TLEs to ' + '"orbcomm1.tle"'

call(['mv','orbcomm0.tle','/export/data_1/rbradley/.predict/orbcomm0.tle'])
call(['mv','orbcomm1.tle','/export/data_1/rbradley/.predict/orbcomm1.tle'])

print '\nmoved "orbcom0.tle" and "orbcom1.tle" into /export/data_1/rbradley/.predict'


