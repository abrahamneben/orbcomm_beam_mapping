#!/usr/bin/python

from date_utils import *

f=open('passinfo','r')
fd=f.readlines()
f.close()

f=open('passinfo_withtimes','w')

for linestr in fd:
	line=linestr.split()
	dyear1,dyear2 = map(float,line[1:3])
	f.write(line[0] + ' ' + dyear2date(dyear1) + ' ' + dyear2date(dyear2) + ' ' + line[3] + '\n')

f.close()