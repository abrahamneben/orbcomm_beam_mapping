

%% load mapfile and assign data to healpix cells

cd('~/Documents/MIT/21cm/sat_cal/updates/2014/jan28/polarized_beam_analysis');

nsides=32;
npix = nSide2nPix(nsides);
fprintf('using Healpix with nsides=%d, res=%fdeg\n',nsides,nSide2res(nsides)/3600);

d='/Users/abrahamn/data/21cm/sat_cal/updates/2013/sep1/phase4/Zenith20130905/';
mapfilename='mapfileZenith20130905_refpolbeams_snrfilt';
[za,az,tileew,refew,tilens,refns,refmodelew,refmodelns,satnum,passnum,hours,pixnums] = import_mapfile(d,mapfilename);

disp('done loading data');

%% for each healpix cell, gather all data inside, and solve for 2 tile beams

tilebeams = zeros(npix,2); % cols are tileew,tilens
modeltilebeams = zeros(npix,2);
counts = zeros(npix,1);

for pixi=1:npix
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

slice1ind=find(abs(ang(:,2))<.05./sin(ang(:,1))|abs(ang(:,2))>2*pi-.05./sin(ang(:,1)));
slice2ind=find(abs(ang(:,2)-pi)<.1./ang(:,1));
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

