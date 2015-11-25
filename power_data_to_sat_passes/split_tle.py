#!/usr/bin/python

## split_tles.py

# this script will split an orbcomm TLE file from celestrak, 
# intoetween 2 files, orbcom1.tle and orbcom2.tle, excluding
# the [-] sats, and will change sat names from, eg. "ORBCOMM FM10 [+]        " to "FM10"

# this script is to be run on apollo

import sys

orbcomfname=sys.argv[1] # excluding the .tle extension

f=open(orbcomfname+'.tle')
orbcommtle=f.readlines()
f.close()

tle1 = open(orbcomfname+'_1.tle','w')
tle2 = open(orbcomfname+'_2.tle','w')

max_num_tle1 = 22
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
print 'wrote ' + str(num_added_to_tle1) + ' orbcomm TLEs to ' + '"orbcom1.tle"'
print 'wrote ' + str(num_added_to_tle2) + ' orbcomm TLEs to ' + '"orbcom2.tle"'


