#!/usr/bin/python


#  below is what an acqFile should look like
#11
#/export/data_2/rbradley/data/satpower20131127.00
#/export/data_2/rbradley/data/satpower20131127.01
#/export/data_2/rbradley/data/satpower20131127.02
#/export/data_2/rbradley/data/satpower20131127.03
#/export/data_2/rbradley/data/satpower20131127.04
#/export/data_2/rbradley/data/satpower20131127.05
#/export/data_2/rbradley/data/satpower20131127.06
#/export/data_2/rbradley/data/satpower20131127.07
#/export/data_2/rbradley/data/satpower20131127.08
#/export/data_2/rbradley/data/satpower20131127.09
#/export/data_2/rbradley/data/satpower20131127.10

dirname = '/export/data_2/rbradley/data/'

import sys

if len(sys.argv)!=3:
	print 'Usage:'
	print './gen_acqFiles.py 20131127 30'
	sys.exit(0)

label = sys.argv[1] # should be something like 20131122
num = int(sys.argv[2])

f = open('acqFiles','w')
f.write(str(num)+'\n')
s=''.join([dirname+'satpower'+label+'.'+'{0:02d}'.format(i)+'\n' for i in range(num)])
f.write(s)
f.close()

