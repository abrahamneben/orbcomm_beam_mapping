
from datetime import datetime

f=open('beamformer_temp_Z02.log')
fd=f.readlines()
f.close()

delta_seconds_dict = {}

for i in range(len(fd)):
	[dt_str,temp] = fd[i].split(',')
	dt = datetime.strptime(dt_str, "%m/%d/%Y %H:%M:%S")
	if i > 0:
		num_sec = (dt-dt_old).total_seconds()
		if num_sec in delta_seconds_dict:
			delta_seconds_dict[num_sec] +=1
		else:
			delta_seconds_dict[num_sec] = 1
		
		if num_sec != 180:
			print [num_sec,fd[i]]
	dt_old = dt


for [k,v] in delta_seconds_dict.items():
	print [k,v]