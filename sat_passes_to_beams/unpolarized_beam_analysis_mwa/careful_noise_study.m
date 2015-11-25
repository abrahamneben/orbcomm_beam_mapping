
cd('/Users/abrahamn/Documents/MIT/21cm/sat_cal/updates/2014/jan28/unpolarized_beam_analysis');

nsides=32;
angcell = pix2ang(nsides);
pixang=cell2mat(angcell)';
 
interleavingtimes = zeros(1,10);
beams = zeros(2,nSide2nPix(nsides),10);
beamind = 1;

%%

label='Zenith_20130905';
disp(['starting ',label]);

strs=strsplit(label,'_');
pointing=strs{1};
delaynums=importdata(['/Users/abrahamn/data/21cm/sat_cal/updates/2013/sep1/phase4/',pointing,'_delaynums.csv']);

% import mapfile and make tile beams
%interleavinghours = .2/3600;
%[za0,az0,tileew0,refew0,tilens0,refns0,refmodelew0,refmodelns0,satnum0,passnum0,hours0,pixnums0] = import_mapfile2_oddeven(label,nsides,0);
%[za1,az1,tileew1,refew1,tilens1,refns1,refmodelew1,refmodelns1,satnum1,passnum1,hours1,pixnums1] = import_mapfile2_oddeven(label,nsides,1);
%[za,az,tileew,refew,tilens,refns,refmodelew,refmodelns,satnum,passnum,hours,pixnums] = import_mapfile2_firstsecondhalf(label,nsides,oddeven); % 0 or 1

interleavinghours = .0004;
[za0,az0,tileew0,refew0,tilens0,refns0,refmodelew0,refmodelns0,satnum0,passnum0,hours0,pixnums0] = import_mapfile2_oddevenwithgiventimescale(label,nsides,0,interleavinghours); % 0 or 1
[za1,az1,tileew1,refew1,tilens1,refns1,refmodelew1,refmodelns1,satnum1,passnum1,hours1,pixnums1] = import_mapfile2_oddevenwithgiventimescale(label,nsides,1,interleavinghours); % 1 or 1

[tilebeamew0,tilebeamns0,tilebeamewstd0,tilebeamnsstd0,tilebeamnumpasses0,tilemodelew,tilemodelns,counts0,outliers0,refpowhpixew0,refpowhpixns0,refmodelhpixewlin0,refmodelhpixnslin0] = make_tilebeams_noisestudy(tileew0,refew0,tilens0,refns0,refmodelew0,refmodelns0,pixnums0,nsides,delaynums,passnum0,satnum0);
[tilebeamew1,tilebeamns1,tilebeamewstd1,tilebeamnsstd1,tilebeamnumpasses1,tilemodelew,tilemodelns,counts1,outliers1,refpowhpixew1,refpowhpixns1,refmodelhpixewlin1,refmodelhpixnslin1] = make_tilebeams_noisestudy(tileew1,refew1,tilens1,refns1,refmodelew1,refmodelns1,pixnums1,nsides,delaynums,passnum1,satnum1);

[tilemodelboresightgainsew,maxewind] = max(tilemodelew);
[tilemodelboresightgainsns,maxnsind] = max(tilemodelns);
tilemodelew = tilemodelew./tilemodelboresightgainsew;
tilemodelns = tilemodelns./tilemodelboresightgainsns;

peakindicesew = find((tilemodelew>tilemodelew(1)/2.)&(counts0>5));
peakindicesns = find((tilemodelns>tilemodelns(1)/2.)&(counts0>5));

tileboresightgainsew = mean(tilebeamew0(peakindicesew)./tilemodelew(peakindicesew));
tileboresightgainsns = mean(tilebeamns0(peakindicesns)./tilemodelns(peakindicesns));
tilemodelew = tilemodelew * tileboresightgainsew;
tilemodelns = tilemodelns * tileboresightgainsns;

interleavingtimes(beamind) = interleavinghours;
beams(1,:,beamind) = tilebeamew0;
beams(2,:,beamind)= tilebeamew1;
beamind = beamind + 1;

%%

% nice_plots;
% semilogy(tilebeamewstd0./tilebeamew0,'k-');hold on;
% semilogy(tilebeamewstd1./tilebeamew1,'r-');
% xlim([0 2000]);
% ylim([0.03 1]);

%%
nice_plots;

%plot_hpix(10*log10(tilebeamew0),counts,[-15 15],1,gbkry);add_polar_grid([.7 .7 .7]);

%plot_slice2_noisestudy(tilebeamewstd0./tilebeamew0,pi/2,'',nsides,1,counts,'ew','r',[0,.5]);% E plane
%plot_slice2_noisestudy(tilebeamewstd1./tilebeamew1,pi/2,'',nsides,1,counts,'ew','b',[0.,5]);% E plane

%plot_slice2_noisestudy(10*log10(tilebeamew0),pi/2,'',nsides,1,counts,'ew','r',[-10 20]);% E plane
%plot_slice2_noisestudy(10*log10(tilebeamew1),pi/2,'',nsides,1,counts,'ew','b',[-10 20]);% E plane

clf;
ha = tight_subplot(2,1,0.075,0.1,0.1);
axes(ha(1));
plot_slice2_noisestudy(10*log10(tilebeamew0./tilemodelew),pi/2,'',nsides,'dB',counts0,'ew','r',[-2 2]);% E plane
plot_slice2_noisestudy(10*log10(tilebeamew1./tilemodelew),pi/2,'',nsides,'dB',counts1,'ew','b',[-2 2]);% E plane
axes(ha(2));
plot_slice2_noisestudy(100*tilebeamewstd0./tilemodelew,pi/2,'',nsides,'%',counts0,'ew','r',[0,30]);% E plane
plot_slice2_noisestudy(100*tilebeamewstd1./tilemodelew,pi/2,'',nsides,'%',counts1,'ew','b',[0,30]);% E plane
title('2.16sec interleaving');

%%
clf;
ha = tight_subplot(1,2,0.05,0.15,0.1);

%[xsort,xsortind,ind1,ind2] = make_slice_indices(tilemodelew,pi/2,'test',nsides,'',counts0,'ew','r',[-1 1]);
%za_on_slice = xsort;

nice_plots;
cols = 'rbkmc';
for i=[1,2]
    for beami = 1:2
        data = [beams(beami,ind2,i)';beams(beami,ind1,i)'];
        model = [tilemodelew(ind2);tilemodelew(ind1)];
        data = data./model;
        
        sorteddata = data(xsortind);
        g = find(sorteddata~=0);disp(i);
        axes(ha(i));
        plot(za_on_slice(g),10*log10(sorteddata(g)),[cols(i),'o-']);ylim([-1 1]);xlim([-11 11]);hold on;
        plot([-100 100],[0 0],'k:');
        xlabel('\theta');
    end
    title([num2str(interleavingtimes(i)*3600),' seconds']);
end
axes(ha(1));
ylabel('dB','rot',0);

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 10 5],'PaperSize',[10 5]);
print('stat_noise_study.pdf','-dpdf','-r250');
