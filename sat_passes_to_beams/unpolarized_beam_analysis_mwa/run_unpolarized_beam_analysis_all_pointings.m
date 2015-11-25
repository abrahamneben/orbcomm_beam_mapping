
cd('/Users/abrahamn/Documents/MIT/21cm/sat_cal/updates/2014/jan28/unpolarized_beam_analysis');

nsides=32;
angcell = pix2ang(nsides);
pixang=cell2mat(angcell)';
 
%labels={'W04S01_20131127','W03S00_20131105','W02S00_20131018','W01S00_20131004','E01S00_20130911','E02S00_20130916','E03S00_20130920','E04S01_20130925'};
%labels={'W03S00_20131105','W02S00_20131018','W01S00_20131004','E01S00_20130911','E02S00_20130916','E03S00_20130920','E04S01_20130925'};
labeldateorder=[5 6 7 8 9 4 3 2 1];
%labels={'Zenith_20130905'};
%labels={'Zenith_20130905','W03S00_20131105',''};
%labels={'W03S00_20131105','W02S00_20131018','W01S00_20131004','Zenith_20130905','E01S00_20130911','E02S00_20130916','E03S00_20130920','E04S01_20130925'};
labels={'Zenith_20130905','W03S00_20131105','E03S00_20130920'};
tileboresightgainsew = zeros(length(labels),1);
tileboresightgainsns = zeros(length(labels),1);
tilemodelboresightgainsew = zeros(length(labels),1);
tilemodelboresightgainsns = zeros(length(labels),1);

for labeli=1:length(labels)
    label=labels{labeli};
    disp(['starting ',label]);
    
    strs=strsplit(label,'_');
    pointing=strs{1};
    delaynums=importdata(['/Users/abrahamn/data/21cm/sat_cal/updates/2013/sep1/phase4/',pointing,'_delaynums.csv']);
    
    % import mapfile and make tile beams
    [za,az,tileew,refew,tilens,refns,refmodelew,refmodelns,satnum,passnum,hours,pixnums] = import_mapfile2(label,nsides);
    [tilebeamew,tilebeamns,tilebeamewstd,tilebeamnsstd,tilebeamnumpasses,tilemodelew,tilemodelns,counts,outliers,refpowhpixew,refpowhpixns,refmodelhpixewlin,refmodelhpixnslin] = make_tilebeams(tileew,refew,tilens,refns,refmodelew,refmodelns,pixnums,nsides,delaynums,passnum,satnum);
    [tilemodelboresightgainsew(labeli),maxewind] = max(tilemodelew);
    [tilemodelboresightgainsns(labeli),maxnsind] = max(tilemodelns);
    tilemodelew = tilemodelew - tilemodelboresightgainsew(labeli);
    tilemodelns = tilemodelns - tilemodelboresightgainsns(labeli);
    disp(tilemodelboresightgainsew(labeli));
    
    % rescale measured and model tile beams to 1 at boresight
    peakindicesew = find((tilemodelew>-3)&(counts>0));
    peakindicesns = find((tilemodelns>-3)&(counts>0));
    mainlobeindicesew = find((tilemodelew>-13)&(counts>0));
    mainlobeindicesns = find((tilemodelns>-13)&(counts>0));
    tileboresightgainsew(labeli) = 10*log10(mean(10.^(.1*(tilebeamew(peakindicesew)-tilemodelew(peakindicesew)))));
    tileboresightgainsns(labeli) = 10*log10(mean(10.^(.1*(tilebeamns(peakindicesns)-tilemodelns(peakindicesns)))));
    tilebeamew = tilebeamew - tileboresightgainsew(labeli);
    tilebeamns = tilebeamns - tileboresightgainsns(labeli);
    tilebeamewstd = tilebeamewstd - tileboresightgainsew(labeli);
    tilebeamnsstd = tilebeamnsstd - tileboresightgainsns(labeli);
    
    % load curtin beams
    curtinbeams = importdata(['curtinbeam_137.5_',pointing,'.csv']);
    g = curtinbeams(:,1)<90*pi/180;
    curtinbeamew = curtinbeams(:,3)-max(curtinbeams(:,3));
    curtinbeamns = curtinbeams(:,4)-max(curtinbeams(:,4));
    
    nice_plots;
    f=figure(1);clf;
    ha = tight_subplot(3,2,0.075,0.1,0.1);
    %ha = tight_subplot(2,2,0.075,0.1,0.1);
    cm=gbkry;
    %cax=[-30 0];
    cax=[-5,5];
    axes(ha(1));
    %plot_hpix(tilebeamew-tilemodelew,counts,cax,1,jet);title(['EW']);add_polar_grid([.7 .7 .7]);
    plot_hpix(tilebeamew,counts,[-30 0],1,cm);title(['EW']);add_polar_grid([.7 .7 .7]);
    %plot_hpix(10.^(.1*tilebeamew)-10.^(.1*tilemodelew),counts,[-.09 .09],1,gbkry);title(['EW']);add_polar_grid([.7 .7 .7]);
    %plot_hpix(10.^(.1*(tilebeamew-tilemodelew)),counts,[.5 1.5],1,jet);title(['EW']);add_polar_grid([.7 .7 .7]);
    axes(ha(2));
    %plot_hpix(tilebeamns-tilemodelns,counts,cax,1,jet);title(['NS']);add_polar_grid([.7 .7 .7]);
    plot_hpix(tilebeamns,counts,[-30 0],1,cm);title(['NS']);add_polar_grid([.7 .7 .7]);
    %plot_hpix(10.^(.1*tilebeamns)-10.^(.1*tilemodelns),counts,[-.09 .09],1,gbkry);title(['NS']);add_polar_grid([.7 .7 .7]);
 
    axes(ha(3));
    plot_slice(tilebeamew,pi/2,'',nsides,maxewind,counts,'ew',tilemodelboresightgainsew(labeli),delaynums);% E plane
    axes(ha(3));
    plot_slice(tilebeamew,0,'',nsides,maxewind,counts,'ew',tilemodelboresightgainsew(labeli),delaynums);% H plane
    
    axes(ha(4));
    plot_slice(tilebeamns,pi/2,'',nsides,maxewind,counts,'ns',tilemodelboresightgainsns(labeli),delaynums);% E plane
    axes(ha(4));
    plot_slice(tilebeamns,0,'',nsides,maxewind,counts,'ns',tilemodelboresightgainsns(labeli),delaynums);% H plane
    
    axes(ha(5));
    plot_slice2(tilebeamew-tilemodelew,pi/2,'',nsides,maxewind,counts,'ew',tilemodelboresightgainsew(labeli),delaynums,'o');% E plane
    plot_slice2(tilebeamew-tilemodelew,0,'',nsides,maxewind,counts,'ew',tilemodelboresightgainsew(labeli),delaynums,'o');% H plane
    plot_slice2(curtinbeamew-tilemodelew,pi/2,'',nsides,maxewind,counts,'ew',tilemodelboresightgainsew(labeli),delaynums,':');% E plane
    plot_slice2(curtinbeamew-tilemodelew,0,'',nsides,maxewind,counts,'ew',tilemodelboresightgainsew(labeli),delaynums,':');% H plane
    
    axes(ha(6));
    plot_slice2(tilebeamns-tilemodelns,pi/2,'',nsides,maxewind,counts,'ns',tilemodelboresightgainsns(labeli),delaynums,'o');% E plane
    plot_slice2(curtinbeamns-tilemodelns,pi/2,'',nsides,maxewind,counts,'ns',tilemodelboresightgainsns(labeli),delaynums,':');% E plane
    plot_slice2(tilebeamns-tilemodelns,0,'',nsides,maxewind,counts,'ns',tilemodelboresightgainsns(labeli),delaynums,'o');% H plane
    plot_slice2(curtinbeamns-tilemodelns,0,'',nsides,maxewind,counts,'ns',tilemodelboresightgainsns(labeli),delaynums,':');% H plane
    
    h = get(gcf,'Children');
    %set(gcf,'Children',[h(3) h(4) h(5) h(1) h(2)]);
    set(gcf,'Children',[h(8) h(6) h(3) h(4) h(5) h(1) h(2) h(7) h(9) h(10) h(11) h(12)]);
    
    cd('~/Documents/MIT/21cm/sat_cal/updates/2014/jan28/unpolarized_beam_analysis');
    set(gcf,'PaperUnits','inches','PaperPosition',[0 0 9 11.5],'PaperSize',[12 10]);
    print([pointing,'_abs.eps'],'-depsc
    ','-r250',f);
 
    %print([pointing,'_nomodel.pdf'],'-dpdf','-r250',f);
   
%     f=figure(1);clf;
%     ha = tight_subplot(1,2,0.075,0.05,0.05);
%     axes(ha(1));
%     plot_hpix(tilebeamnumpasses,counts,[0 15],1,gbkry);title(['log_{10}(# passes)']);add_polar_grid([.7 .7 .7]);
%     axes(ha(2));
%     plot_hpix(10.^(.1*(tilebeamewstd-tilebeamew))*100,counts,[0 20],1,gbkry);title(['% scatter']);add_polar_grid([.7 .7 .7]);
%     %set(gcf,'PaperUnits','inches','PaperPosition',[0 0 10 5],'PaperSize',[10 5]);
    %%%%print([pointing,'.eps'],'-depsc','-r100',f);
    %print('zenith_numpasses_percentscatter.pdf','-dpdf','-r250',f);
%    
%     cd('~/Documents/MIT/21cm/sat_cal/updates/2014/jan28/unpolarized_beam_analysis');
%     nice_plots;
%     f=figure(1);clf;
%     ha = tight_subplot(1,2,0.075,0.05,0.05);
%     axes(ha(1));
%     plot_hpix(log10(counts),counts,[0 3],1,gbkry);title(['# data points']);add_polar_grid([.7 .7 .7]);
%     axes(ha(2));
%     plot_hpix(outliers,counts,[0 20],1,gbkry);title(['# outliers']);add_polar_grid([.7 .7 .7]);
%     set(gcf,'PaperUnits','inches','PaperPosition',[0 0 10 5],'PaperSize',[10 5]);
%     print('num_datapoints_in_cells_and_outliers.pdf','-dpdf','-r250',f);
%     
%    
    disp(['done with ',label]);
end


%%

nice_plots;
f=figure(1);clf;
ha = tight_subplot(1,2,0.075,0.1,0.1);
cax=[-2,2];
axes(ha(1));
plot_hpix(tilebeamew-tilemodelew,counts,cax,1,jet);title(['MWA EW Beam / Analytic Model (dB)']);add_polar_grid([.7 .7 .7]);
axes(ha(2));
plot_hpix(tilebeamns-tilemodelns,counts,cax,1,jet);title(['MWA NS Beam / Analytic Model (dB)']);add_polar_grid([.7 .7 .7]);


%% AAS poster

%plot_hpix(tilebeamew,counts,[-30 0],1,jet);add_polar_grid([.7 .7 .7]);
%plot_hpix(tilebeamew-tilemodelew,counts,[-5 5],1,gbkry);add_polar_grid([.7 .7 .7]);
%set(gcf,'PaperUnits','inches','PaperPosition',[0 0 10 10],'PaperSize',[10 10]);
%print('zenith_for_poster_relative.pdf','-dpdf','-r250');

plot_slice_polar(tilebeamew,pi/2,'',nsides,maxewind,counts,'ew',tilemodelboresightgainsew(labeli),delaynums);% E plane
%plot_slice_polar(tilebeamew,0,'',nsides,maxewind,counts,'ew',tilemodelboresightgainsns(labeli),delaynums);% H plane
set(gcf,'PaperUnits','inches','PaperPosition',[0 0 10 10],'PaperSize',[10 10]);
print('zenith_slice_for_poster.pdf','-dpdf','-r100');
%save2pdf('zenith_slice_for_poster.pdf');

%% export zenith beam in healpix

    g = (counts>0)&(tilemodelew>-25)&(tilemodelns>-25);
    ang = cell2mat(pix2ang(nsides,find(g)));
    ang = reshape(ang,2,length(ang)/2)';
    za=ang(:,1);
    az=ang(:,2);
    
    plot_hpix(tilebeamew-tilemodelew,(counts>0)&(tilemodelew>-25),cax,1,hot);title(['EW']);add_polar_grid([.7 .7 .7]);colormap(gbkry);
    
    polar(az,za,'.');

    cd('~/Documents/MIT/21cm/sat_cal/updates/2014/jan28/unpolarized_beam_analysis');
    dlmwrite('Zenith_20130905_measuredbeam_25dbcutoff.csv',[za,az,tilebeamew(g),tilemodelew(g),tilebeamns(g),tilemodelns(g),find(g)],',');
    
%% load gains derived from sky noise data

sysgains = zeros(length(labels),4);
for labeli=1:length(labels)
    label=labels{labeli};
    skydataraw=importdata(['/Users/abrahamn/Documents/MIT/21cm/sat_cal/updates/2013/sep1/phase4/',label,'/mapfile',label,'_sky.csv']);
    skydat=skydataraw.data;
    sysgains(labeli,:) = median(skydat(:,2:5));
end

figure(2);
plot(sysgains(labeldateorder,:));
legend({'tileew','refew','tilens','refns'});


%%

nice_plots;
figure(1);
plot(tileboresightgainsew+5,'bo');hold on;
plot(tileboresightgainsns+1.75,'ro');

plot(tilemodelboresightgainsew,'b-');
plot(tilemodelboresightgainsns,'r-');
xlabel('pointing number, from W04S01 to E04S01');
ylabel('dB');
title('tile boresight gains');
legend({'EW','NS','model EW','model NS'},'Location','South');

%%

figure(1);
plot(tileboresightgainsns(labeldateorder)+5-tilemodelboresightgainsew(labeldateorder),'bo');hold on;
plot(tileboresightgainsew(labeldateorder)+5-tilemodelboresightgainsew(labeldateorder),'ro');
xlabel('pointings in date order');
ylabel('dB');
title('tile boresight gains relative to model');
legend({'data - model EW','data - model NS'});

%% export za/az of healpix nsides

nsides=64;
ang = cell2mat(pix2ang(nsides));
polar(ang(2,:),ang(1,:),'.');

cd('~/Documents/MIT/21cm/sat_cal/updates/2014/jan28/unpolarized_beam_analysis');
dlmwrite('healpix_64sides_za_and_az.csv',ang',',');

