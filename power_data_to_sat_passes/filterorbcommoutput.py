#!/users/aneben/python/bin/python

import sys
import commands

months={'Jan':'01','Feb':'02','Mar':'03','Apr':'04','May':'05','Jun':'06','Jul':'07','Aug':'08','Sept':'09','Oct':'10','Nov':'11','Dec':'12'}
label=sys.argv[1]

commands.getoutput("cat ../phase3/composite_"+label+"/orbcomm* | grep Sync | grep -v '?' | awk '{print $1,$2,$3}' | sed 's/Rx\[//'| sed 's/Sync(/ /' | sed 's/\*//' | sed 's/|[0-9]*\.00\]//' | sed 's/://' | sed 's/://' | awk 'NR % 4 == 0' > ../phase3/composite_"+label+"/"+label+"_filteredorbcommout.txt")

f=open("../phase3/composite_"+label+"/"+label+"_filteredorbcommout.txt")
fd=f.readlines()
f.close()

f=open("../phase3/composite_"+label+"/"+label+"_filteredorbcommout.txt",'w')

for line in fd:
	ls=line.split()
	daymonyear = ls[0]
	day = daymonyear[0:2]
	mon = months[daymonyear[2:5]]
	year = daymonyear[5:7]
	f.write('20'+year+mon+day+ls[1]+' '+ls[2]+' '+ls[3]+'\n')

f.close()

