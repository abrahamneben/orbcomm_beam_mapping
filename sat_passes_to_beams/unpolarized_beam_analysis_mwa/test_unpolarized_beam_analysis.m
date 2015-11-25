
%% load mapfile and assign data to healpix cells

cd('~/Documents/MIT/21cm/sat_cal/updates/2014/jan28/polarized_beam_analysis');

nsides=32;
npix = nSide2nPix(nsides);
fprintf('using Healpix with nsides=%d, res=%fdeg\n',nsides,nSide2res(nsides)/3600);

d='/Users/abrahamn/data/21cm/sat_cal/updates/2013/sep1/phase4/Zenith20130905/';
mapfilename='mapfileZenith20130905_refpolbeams_snrfilt';
[za,az,tileew,refew,tilens,refns,refmodelewtheta,refmodelewphi,refmodelnstheta,refmodelnsphi,satnum,passnum,hours] = import_mapfile(d,mapfilename);
refmodelew = 10*log10(10.^(.1*refmodelewphi)+10.^(.1*refmodelewtheta));
refmodelns = 10*log10(10.^(.1*refmodelnsphi)+10.^(.1*refmodelnstheta));

angarr = arrayfun(@(x,y)([x;y]),za,az,'UniformOutput',false);
pixnums = ang2pix(nsides,angarr);

% correct for system gains estimated by looking at the sky noise plot
refnsgain = 2.5;
tilensgain = 0.25;
refns = refns + refnsgain;
tilens = tilens + tilensgain;

disp('done loading data');

%% for each healpix cell, gather all data inside, and solve for 2 tile beams

tilebeams = zeros(npix,2); % cols are tileew,tilens
modeltilebeams = zeros(npix,2);
counts = zeros(npix,1);

%for pixi=1:npix
for pixi=100:102
    ang = pix2ang(nsides,pixi);
    pixza = ang{1}(1);
    pixaz = ang{1}(2);
    modeltilebeams(pixi,:) = 10*log10([1-sin(pixza)^2*sin(pixaz)^2,1-sin(pixza)^2*cos(pixaz)^2]*array_factor_and_ground_screen_power_beam(pixza,pixaz));

    ind = find(pixnums==pixi);
    n = length(ind);
    if n<2
        continue;
    end
    if mod(pixi,1000)==0
        fprintf('pixi=%d/%d\n',pixi,npix);
    end
    counts(pixi) = n;

    %tilebeams(pixi,:) = 10*log10(mean(10.^.1*[tileew(ind)-refew(ind)+refmodelew(ind),tilens(ind)-refns(ind)+refmodelns(ind)]));
    tilebeams(pixi,:) = mean([tileew(ind)-refew(ind)+refmodelew(ind),tilens(ind)-refns(ind)+refmodelns(ind)]);
end

disp('done gridding');

%% chisq map
%plot_hpix(10*log10(redchisq),counts,[-40 0],1,jet);title('\chi^2_{red}');

%% find the main lobe indices

countsmainlobe = zeros(npix,1);
for pixi=1:npix
    if counts(pixi)==0
        continue;
    end
    ang = pix2ang(nsides,pixi);
    pixza = ang{1}(1);
    pixaz = ang{1}(2);
    
    if pixza<30*pi/180
        countsmainlobe(pixi)=1;
    end
end
mainlobeindices=find(countsmainlobe);

%% plot total power NS and EW beams with a rotation of the tile models

datew=tilebeams(:,1);
modelew=modeltilebeams(:,1);
gew=median(datew(mainlobeindices)-modelew(mainlobeindices));
modelew=modelew+gew;
chisqew=norm(10.^(.1*datew(mainlobeindices))-10.^(.1*modelew(mainlobeindices)))^2;

datns=tilebeams(:,2);
modelns=modeltilebeams(:,2);
gns=median(datns(mainlobeindices)-modelns(mainlobeindices));
modelns=modelns+gns;
chisqns=norm(10.^(.1*datns(mainlobeindices))-10.^(.1*modelns(mainlobeindices)))^2;

figure;
ha = tight_subplot(1,2,0.1,0.1,0.1);
cm=gbkry;
cax=[-2 2]*2;
axes(ha(1));
plot_hpix(datew-modelew,counts,cax,1,cm);title('EW');
axes(ha(2));
plot_hpix(datns-modelns,counts,cax,1,cm);title('NS');


%% plot slices through E and H planes of total power beams

angcell = pix2ang(nsides,1:npix);
ang=cell2mat(angcell)';

greatcircleangle

slice1ind=find(abs(ang(:,2))<.05./sin(ang(:,1))|abs(ang(:,2))>2*pi-.05./sin(ang(:,1)));
slice2ind=find(abs(ang(:,2)-pi)<.1./ang(:,1));
%slice1ind=find(abs(ang(:,2))<.05./sin(ang(:,1))|abs(ang(:,2))>2*pi-.05./sin(ang(:,1)));
%slice2ind=find(abs(ang(:,2)-pi)<.1./ang(:,1));
slice1ind=intersect(find(counts>10),slice1ind);
slice2ind=intersect(find(counts>10),slice2ind);
slice1ind=intersect(mainlobeindices,slice1ind);
slice2ind=intersect(mainlobeindices,slice2ind);

slice3ind=find(abs(ang(:,2)-pi/2)<.1./ang(:,1));
slice4ind=find(abs(ang(:,2)-4/3*pi)<.1./ang(:,1));
slice3ind=intersect(find(counts>10),slice3ind);
slice4ind=intersect(find(counts>10),slice4ind);
slice3ind=intersect(mainlobeindices,slice3ind);
slice4ind=intersect(mainlobeindices,slice4ind);

subplot(221);
plot(180/pi*ang(slice1ind,1),10.^(.1*datew(slice1ind)),'r.');hold on;
plot(-180/pi*ang(slice2ind,1),10.^(.1*datew(slice2ind)),'r.');hold on
plot(180/pi*ang(slice1ind,1),10.^(.1*modelew(slice1ind)-.07),'k-');hold on;
plot(-180/pi*ang(slice2ind,1),10.^(.1*modelew(slice2ind)-.07),'k-');
title('EW E');xlim([-30 30]);

subplot(222);
plot(180/pi*ang(slice3ind,1),10.^(.1*datew(slice3ind)),'r.');hold on;
plot(-180/pi*ang(slice4ind,1),10.^(.1*datew(slice4ind)),'r.');hold on
plot(180/pi*ang(slice3ind,1),10.^(.1*modelew(slice3ind)-.07),'k-');hold on;
plot(-180/pi*ang(slice4ind,1),10.^(.1*modelew(slice4ind)-.07),'k-');
title('EW H');xlim([-30 30]);

subplot(223);
plot(180/pi*ang(slice1ind,1),10.^(.1*datns(slice1ind)),'r.');hold on;
plot(-180/pi*ang(slice2ind,1),10.^(.1*datns(slice2ind)),'r.');hold on
plot(180/pi*ang(slice1ind,1),10.^(.1*modelns(slice1ind)-.02),'k-');hold on;
plot(-180/pi*ang(slice2ind,1),10.^(.1*modelns(slice2ind)-.02),'k-');
title('NS H');xlim([-30 30]);

subplot(224);
plot(180/pi*ang(slice3ind,1),10.^(.1*datns(slice3ind)),'r.');hold on;
plot(-180/pi*ang(slice4ind,1),10.^(.1*datns(slice4ind)),'r.');hold on
plot(180/pi*ang(slice3ind,1),10.^(.1*modelns(slice3ind)-.015),'k-');hold on;
plot(-180/pi*ang(slice4ind,1),10.^(.1*modelns(slice4ind)-.015),'k-');
title('NS E');xlim([-30 30]);


%% mainlobe+sidelobes (dB)

angcell = pix2ang(nsides,1:npix);
ang=cell2mat(angcell)';

slice1ind=find(abs(ang(:,2))<.05./sin(ang(:,1))|abs(ang(:,2))>2*pi-.05./sin(ang(:,1)));
slice2ind=find(abs(ang(:,2)-pi)<.1./ang(:,1));
slice1ind=intersect(find(counts>10),slice1ind);
slice2ind=intersect(find(counts>10),slice2ind);
%slice1ind=intersect(mainlobeindices,slice1ind);
%slice2ind=intersect(mainlobeindices,slice2ind);

slice3ind=find(abs(ang(:,2)-pi/2)<.1./ang(:,1));
slice4ind=find(abs(ang(:,2)-4/3*pi)<.1./ang(:,1));
slice3ind=intersect(find(counts>10),slice3ind);
slice4ind=intersect(find(counts>10),slice4ind);
%slice3ind=intersect(mainlobeindices,slice3ind);
%slice4ind=intersect(mainlobeindices,slice4ind);

xrange=[-1,1]*80;yrange=[-20 20];

subplot(221);
plot(180/pi*ang(slice1ind,1),datew(slice1ind),'r.');hold on;
plot(-180/pi*ang(slice2ind,1),datew(slice2ind),'r.');hold on
plot(180/pi*ang(slice1ind,1),modelew(slice1ind)-.07,'k-');hold on;
plot(-180/pi*ang(slice2ind,1),modelew(slice2ind)-.07,'k-');
title('EW E');xlim(xrange);ylim(yrange);

subplot(222);
plot(180/pi*ang(slice3ind,1),datew(slice3ind),'r.');hold on;
plot(-180/pi*ang(slice4ind,1),datew(slice4ind),'r.');hold on
plot(180/pi*ang(slice3ind,1),modelew(slice3ind)-.07,'k-');hold on;
plot(-180/pi*ang(slice4ind,1),modelew(slice4ind)-.07,'k-');
title('EW H');xlim(xrange);ylim(yrange);

subplot(223);
plot(180/pi*ang(slice1ind,1),datns(slice1ind),'r.');hold on;
plot(-180/pi*ang(slice2ind,1),datns(slice2ind),'r.');hold on
plot(180/pi*ang(slice1ind,1),modelns(slice1ind)-.02,'k-');hold on;
plot(-180/pi*ang(slice2ind,1),modelns(slice2ind)-.02,'k-');
title('NS H');xlim(xrange);ylim(yrange);

subplot(224);
plot(180/pi*ang(slice3ind,1),datns(slice3ind),'r.');hold on;
plot(-180/pi*ang(slice4ind,1),datns(slice4ind),'r.');hold on
plot(180/pi*ang(slice3ind,1),modelns(slice3ind)-.015,'k-');hold on;
plot(-180/pi*ang(slice4ind,1),modelns(slice4ind)-.015,'k-');
title('NS E');xlim(xrange);ylim(yrange);



%%

clf;plot(180/pi*ang(mainlobeindices,1),10.^(.1*(datew(mainlobeindices)-modelew(mainlobeindices)-.06)),'.');ylim([0 2]);

%% plot total power beams

ha = tight_subplot(1,2,0.05,0.07,0.1);
cax=[-1 1]*3;
axes(ha(1));
dat=10*log10(10.^(.1*tilebeams(:,1))+10.^(.1*tilebeams(:,2)))-18;
model=10*log10(10.^(.1*modeltilebeams(:,1))+10.^(.1*modeltilebeams(:,2)))-22.5;
plot_hpix(dat-model+.5,counts,cax,1,gbkry);title('E data/model (dB)');

axes(ha(2));
dat=10*log10(10.^(.1*tilebeams(:,3))+10.^(.1*tilebeams(:,4)))-18;
model=10*log10(10.^(.1*modeltilebeams(:,3))+10.^(.1*modeltilebeams(:,4)))-22.5;
plot_hpix(dat-model-.5,counts,cax,1,gbkry);title('NS data/model (dB)');

%% plot NS beams and models

ha = tight_subplot(1,2,0.05,0.07,0.1);
cax=[-1 1]*10;
axes(ha(1));
plot_hpix(tilebeams(:,3)-modeltilebeams(:,3)+4,counts,cax,1,gbkry);title('NS_\theta data/model (dB)');

axes(ha(2));
plot_hpix(tilebeams(:,4)-modeltilebeams(:,4)+4,counts,cax,1,gbkry);title('NS_\phi data/model (dB)');
