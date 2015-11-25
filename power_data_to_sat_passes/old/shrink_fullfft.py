f=open('../compositeZ02/passdataforsat5_fullfft','r')
fd=f.readlines()
f.close()

fshrunk=open('../compositeZ02/passdataforsat5_fullfft_shrunk','w')

for i in range(len(fd)/512):
	if i % 4 == 0:
		for j in range(512):
			fshrunk.write(fd[512*i+j])

fshrunk.close()