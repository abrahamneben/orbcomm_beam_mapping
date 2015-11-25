
cd('/Users/abrahamn/Documents/MIT/21cm/sat_cal/updates/2014/jan28/unpolarized_beam_analysis');

nsides=32;
angcell = pix2ang(nsides);
pixang=cell2mat(angcell)';
 
labeldateorder=[5 6 7 8 9 4 3 2 1];
labels={'Zenith_20130905'};

label=labels{1};
disp(['starting ',label]);

strs=strsplit(label,'_');
pointing=strs{1};
delaynums=importdata(['/Users/abrahamn/data/21cm/sat_cal/updates/2013/sep1/phase4/',pointing,'_delaynums.csv']);

%% load first half data

% import mapfile and make tile beams
[za,az,tileew,refew,tilens,refns,refmodelew,refmodelns,satnum,passnum,hours,pixnums] = import_mapfile2_firstsecondhalf(label,nsides,1);
[tilebeamew,tilebeamns,tilebeamewstd,tilebeamnsstd,tilebeamnumpasses,tilemodelew,tilemodelns,counts,outliers,refpowhpixew,refpowhpixns,refmodelhpixewlin,refmodelhpixnslin] = make_tilebeams(tileew,refew,tilens,refns,refmodelew,refmodelns,pixnums,nsides,delaynums,passnum,satnum);
[tilemodelboresightgainew,maxewind] = max(tilemodelew);
[tilemodelboresightgainns,maxnsind] = max(tilemodelns);
tilemodelew = tilemodelew - tilemodelboresightgainew;
tilemodelns = tilemodelns - tilemodelboresightgainns;
disp(tilemodelboresightgainew);

peakindicesew = find((tilemodelew>-3)&(counts>0));
peakindicesns = find((tilemodelns>-3)&(counts>0));
mainlobeindicesew = find((tilemodelew>-13)&(counts>0));
mainlobeindicesns = find((tilemodelns>-13)&(counts>0));
tileboresightgainsew = 10*log10(mean(10.^(.1*(tilebeamew(peakindicesew)-tilemodelew(peakindicesew)))));
tileboresightgainsns = 10*log10(mean(10.^(.1*(tilebeamns(peakindicesns)-tilemodelns(peakindicesns)))));
tilebeamew = tilebeamew - tileboresightgainsew(1);
tilebeamns = tilebeamns - tileboresightgainsns(1);
tilebeamewstd = tilebeamewstd - tileboresightgainsew(1);
tilebeamnsstd = tilebeamnsstd - tileboresightgainsns(1);


%%
nice_plots;
f=figure;clf;
ha = tight_subplot(1,2,0.075,0.1,0.1);
cm=gbkry;
cax=[-5,5];
axes(ha(1));
plot_hpix(tilebeamew-tilemodelew,counts,cax,1,hot);title(['EW, second half']);add_polar_grid([.7 .7 .7]);
axes(ha(2));
plot_hpix(tilebeamns-tilemodelns,counts,cax,1,cm);title(['NS, second half']);add_polar_grid([.7 .7 .7]);

    