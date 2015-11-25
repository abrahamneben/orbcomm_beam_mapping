
cd('/Users/abrahamn/Documents/MIT/21cm/sat_cal/updates/2014/jan28/unpolarized_beam_analysis');

nsides=32;

label='null2';
disp(['starting ',label]);

[za,az,tileew,refew,tilens,refns,refmodelew,refmodelns,satnum,passnum,hours,pixnums] = import_mapfile2_null2(nsides);
[tilebeamew,tilebeamns,counts,tilebeamnumpasses,outliers] = make_tilebeams_null2(tileew,refew,tilens,refns,refmodelew,refmodelns,pixnums,nsides,passnum,satnum);
[refmodelew,refmodelns] = make_ref_model_beams(nsides);
refmodelboresightgainew = max(refmodelew);
refmodelboresightgainns = max(refmodelns);
refmodelew = refmodelew - refmodelboresightgainew;
refmodelns = refmodelns - refmodelboresightgainns;

peakindicesew = find((refmodelew>-3)&(counts>0));
peakindicesns = find((refmodelns>-3)&(counts>0));

tileboresightgainsew = 10*log10(average_excluding_outliers(10.^(.1*(tilebeamew(peakindicesew)-refmodelew(peakindicesew)))));
tileboresightgainsns = 10*log10(average_excluding_outliers(10.^(.1*(tilebeamns(peakindicesns)-refmodelns(peakindicesns)))));
tilebeamew = tilebeamew - tileboresightgainsew;
tilebeamns = tilebeamns - tileboresightgainsns;

fprintf(['\n',num2str(length(find(counts))/(nSide2nPix(nsides)/2)*100),'percent sky coverage\n']);
fprintf(['\n',num2str(length(hours)*(1/6)/3600),' hours of data\n\n']);
fprintf(['\n',num2str(nSide2res(nsides)/3600),' deg resolution\n\n']);

fprintf(['\n',num2str(length(unique(passnum*10+satnum))),' passes']);

%%

f=figure(1);clf;
ha = tight_subplot(3,2,0.075,0.1,0.1);
cm=gbkry;
cax=[-1.5 1.5];
axes(ha(1));
%plot_hpix(tilebeamew-refmodelew,counts,cax,1,cm);title(['EW']);add_polar_grid([.7 .7 .7]);
plot_hpix(tilebeamew,counts,[-20 0],1,cm);title(['EW']);add_polar_grid([.7 .7 .7]);
axes(ha(2));
%plot_hpix(tilebeamns-refmodelns,counts,cax,1,cm);title(['NS']);add_polar_grid([.7 .7 .7]);
plot_hpix(tilebeamns,counts,[-20 0],1,cm);title(['NS']);add_polar_grid([.7 .7 .7]);

axes(ha(3));
plot_slice_null2(tilebeamew,pi/2,'',nsides,counts,'ew',refmodelboresightgainew);% E plane
axes(ha(3));
plot_slice_null2(tilebeamew,0,'',nsides,counts,'ew',refmodelboresightgainew);% H plane

axes(ha(4));
plot_slice_null2(tilebeamns,pi/2,'',nsides,counts,'ns',refmodelboresightgainns);% E plane
axes(ha(4));
plot_slice_null2(tilebeamns,0,'',nsides,counts,'ns',refmodelboresightgainns);% H plane

axes(ha(5));
plot_slice2_null2(tilebeamew-refmodelew,pi/2,'',nsides,counts,'ew',refmodelboresightgainew);% E plane
plot_slice2_null2(tilebeamew-refmodelew,0,'',nsides,counts,'ew',refmodelboresightgainew);% H plane

axes(ha(6));
plot_slice2_null2(tilebeamns-refmodelns,pi/2,'',nsides,counts,'ns',refmodelboresightgainns);% E plane
plot_slice2_null2(tilebeamns-refmodelns,0,'',nsides,counts,'ns',refmodelboresightgainns);% H plane

h = get(gcf,'Children');
set(gcf,'Children',[h(8) h(6) h(1) h(2) h(3) h(4) h(5) h(7) h(9) h(10) h(11) h(12)]);    

cd('~/Documents/MIT/21cm/sat_cal/updates/2014/jan28/unpolarized_beam_analysis');
set(gcf,'PaperUnits','inches','PaperPosition',[0 0 10 13],'PaperSize',[10 13]);
print('null2_abs.pdf','-dpdf','-r250',f);
%print('null2_rel.pdf','-dpdf','-r250',f);


%%
% plot_slice_null2(tilebeamew,pi/2,'Null2 EW E plane',nsides,counts,'ew',refmodelboresightgainew);
% plot_slice_null2(tilebeamew,0,'Null2 EW H plane',nsides,counts,'ew',refmodelboresightgainew);
% plot_slice_null2(tilebeamns,pi/2,'Null2 NS H plane',nsides,counts,'ns',refmodelboresightgainns);
% plot_slice_null2(tilebeamns,0,'Null2 NS E plane',nsides,counts,'ns',refmodelboresightgainns);
% 
% %%
% 
% f=figure(1);clf;
% ha = tight_subplot(1,2,0.1,0.1,0.1);
% cm=gbkry;
% cax=[-1 1]*5;
% axes(ha(1));
% plot_hpix(tilebeamew-refmodelew,counts,cax,1,cm);title('Null2 EW');add_polar_grid([1 1 1]);
% axes(ha(2));
% plot_hpix(tilebeamns-refmodelns,counts,cax,1,cm);title('Null2 NS');add_polar_grid([1 1 1]);
% set(gcf,'PaperUnits','inches','PaperPosition',[0 0 10 5]);
% set(gca,'FontSize',12,'FontWeight','bold','linewidth',2);
% print('null2_map.png','-dpng','-r100',f);
% 
% disp(['done with ',label])

