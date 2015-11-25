cd('~/Documents/MIT/21cm/sat_cal/updates/satcalanalysis/tileModel');

beamdatans=importdata('tileNS_E04S01.tsv');
beamdataew=importdata('tileEW_E04S01.tsv');

theta=beamdatans(:,1);
phi=beamdatans(:,2);
beamns=beamdatans(:,3);
beamew=beamdataew(:,3);

x=theta.*cos(phi*pi/180);
y=theta.*sin(phi*pi/180);

%%

%scatter(x,y,10,beam);colorbar;

subplot(121);
scatter(phi,theta,10,beamns);colorbar;
subplot(122);
scatter(phi,theta,10,beamew);colorbar;
