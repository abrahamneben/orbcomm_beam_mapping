import healpy as hp
import numpy as n
import sys
import matplotlib.pyplot as plt

c=3.e8
f=137.5e6
lamb = c/f
h=0.3
vmin=-10

# Hertzian Dipole model
nsides = 8
npixels = hp.nside2npix(nsides)
thetas,phis = hp.pix2ang(nsides,n.arange(npixels))
hpower = (1-n.sin(thetas)**2*n.cos(phis)**2)*n.sin(2*n.pi*h*n.cos(thetas)/lamb)**2
hpower = 10*n.log10(hpower)-100*(thetas>n.pi/2)
hpower -= hpower.max()
hp.mollview(hpower,rot=[0,90,0],cmap='gnuplot',min=vmin,unit='dB',title=r'Hertzian Dipole Model')


#infile = sys.argv[1]
infile = 'new_ref_dipole_model_137_31july2015.txt'
#infile = 'ff137_5_xpol.txt'
rawdata = n.genfromtxt(infile,dtype='float',skip_header=3,usecols=(0,1,2))
thetas = rawdata[:,0]
phis = rawdata[:,1]
thetas = thetas*n.pi/180.
phis = phis*n.pi/180.
hpower = n.zeros(npixels)
pixInd = hp.ang2pix(nsides,thetas,phis)
hpower[pixInd] = rawdata[n.arange(len(thetas)),2]
hpower = hpower - hpower.max()
hp.mollview(hpower,rot=[0,90,0],cmap='gnuplot',title=infile+' Model',unit='dB',format='%d',min=vmin)
plt.show()
