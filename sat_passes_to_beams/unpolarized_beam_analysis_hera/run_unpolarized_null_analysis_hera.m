% load Dave's dish model

dishmodeldat = importdata('/Users/abrahamn/Documents/MIT/21cm/sat_cal/updates/satcalanalysis/dishModel/hat137.csv');

dishmodeltheta = dishmodeldat.data(:,1);
gain = max(dishmodeldat.data(:,2));
dishmodelaz0 = dishmodeldat.data(:,2)-gain;
dishmodelaz90 = dishmodeldat.data(:,20)-gain;

figure(11);
plot(dishmodeltheta,dishmodelaz0,'r-');hold on;
plot(dishmodeltheta,dishmodelaz90,'r--');

%% load CST 140MHz model

npix = nSide2nPix(32);
cd('/Users/abrahamn/Documents/MIT/21cm/hera/2015/jul13/unpolarized_beam_analysis_hera');
cstdishmodel = 10*log10(importdata('/Users/abrahamn/Documents/MIT/21cm/hera/2015/sim_vis_with_orbcomm_hera_beams/HERA_DISH_paper_feed_cyl36_140mhz_Y_healpix_nside32.txt'));
cstdishmodel = cstdishmodel-max(cstdishmodel);
%zaaz = cell2mat(pix2ang(32));
%za = zaaz(1,1:npix/2);
%az = zaaz(2,1:npix/2);
%az(az>pi) = az(az>pi)-2*pi;

%g=abs(az)<10.*pi/180.;
%g2=abs(az-pi/2)<10.*pi/180.;
%figure(11);
%plot(za(g)*180./pi,cstdishmodel(g),'b-');hold on;
%plot(za(g2)*180./pi,cstdishmodel(g2),'b--');

figure(11);
plot_hpix_model_on_slice(cstdishmodel,32,0,'r');
plot_hpix_model_on_slice(cstdishmodel,32,pi/2,'b');

%% load feed model

feedmodeldat = importdata('/Users/abrahamn/Documents/MIT/21cm/sat_cal/updates/satcalanalysis/feedModel/FF140Mhz_dipole_only.txt');
feedmodelza = feedmodeldat.data(:,1);
feedmodelaz = feedmodeldat.data(:,2);
feedmodel = feedmodeldat.data(:,3);
feedmodel = feedmodel - max(feedmodel);

g = feedmodelza<90;
feedmodelza = feedmodelza(g);
feedmodelaz = feedmodelaz(g);
feedmodel = feedmodel(g);

feedmodelslice1za = [-flipud(feedmodelza(feedmodelaz==0));feedmodelza(feedmodelaz==180)];
feedmodelslice1 = [flipud(feedmodel(feedmodelaz==0));feedmodel(feedmodelaz==180)];
feedmodelslice2za = [-flipud(feedmodelza(feedmodelaz==90));feedmodelza(feedmodelaz==270)];
feedmodelslice2 = [flipud(feedmodel(feedmodelaz==90));feedmodel(feedmodelaz==270)];
plot(feedmodelslice1za,feedmodelslice1);hold on;plot(feedmodelslice2za,feedmodelslice2);
a=pi/180;
figure;
scatter(sin(feedmodelza*a).*sin(feedmodelaz*a),sin(feedmodelza*a).*cos(feedmodelaz*a),25,feedmodel,'filled');
%colorbar;
%caxis([-35,-18]);

%%

cd('/Users/abrahamn/Documents/MIT/21cm/hera/2015/jul13/unpolarized_beam_analysis_hera');

nsides=32;

%labels={'null3','null4'};
%labels={'dish3','dish1','dish2','dish4'};
%labels={'dish4'};
%labels={'null1','null3','null4'};
%titles={'feed on ground'};
%titles={'feed @ 4m','feed @ 4.5m','feed @ 5m','feed @ 5.3m'};
titles={'null1','null3','null4'};
for labeli=1:length(labels)
    label=labels{labeli};
    plottitle=titles{labeli};
    disp(['starting ',label,'\t']);

    [za,az,tileew,refew,tilens,refns,refmodelewdataorder,refmodelnsdataorder,satnum,passnum,hours,pixnums] = import_mapfile2_null(nsides,label);
    [refmodelew,refmodelns] = make_ref_model_beams(nsides);
    [tilebeamew,tilebeamns,counts,tilebeamnumpasses,outliers] = make_tilebeams_null2(tileew,refew,tilens,refns,refmodelewdataorder,refmodelnsdataorder,pixnums,nsides,passnum,satnum);

    refmodelboresightgainew = max(refmodelew);
    refmodelboresightgainns = max(refmodelns);
    refmodelew = refmodelew - refmodelboresightgainew;
    refmodelns = refmodelns - refmodelboresightgainns;

    peakindicesew = find((refmodelew>-3)&(counts>0));
    peakindicesns = find((refmodelns>-3)&(counts>0));
    tileboresightgainsew = 10*log10(average_excluding_outliers(10.^(.1*(tilebeamew(peakindicesew)-refmodelew(peakindicesew)))));
    tileboresightgainsns = 10*log10(average_excluding_outliers(10.^(.1*(tilebeamns(peakindicesns)-refmodelns(peakindicesns)))));
    %tileboresightgainsew = max(tilebeamew(1:100));
    %tileboresightgainsns = max(tilebeamns(1:100)); 
    tilebeamew = tilebeamew - tileboresightgainsew;
    tilebeamns = tilebeamns - tileboresightgainsns;

    fprintf(['\n',num2str(length(find(counts))/(nSide2nPix(nsides)/2)*100),'percent sky coverage\n']);
    fprintf(['\n',num2str(length(hours)*(1/6)/3600),' hours of data\n\n']);
    fprintf(['\n',num2str(nSide2res(nsides)/3600),' deg resolution\n\n']);
    fprintf(['\n',num2str(length(unique(passnum*10+satnum))),' passes']);

    %cd('/Users/abrahamn/Documents/MIT/21cm/hera/2015/jul13/unpolarized_beam_analysis_hera');
    csvwrite([label,'_north_over_south_ratio_ew_ns.csv'],[tilebeamew-refmodelew,tilebeamns-refmodelns,counts]);

    continue;
    
    % export beams 
    csvwrite([label,'_nside',num2str(nsides),'_ew_ns.csv'],[tilebeamew.*(counts>0),tilebeamns.*(counts>0)]);

    %continue;

    % make standard 6 panel plot (relative beams, cuts through absolute beams
    %  and cuts through relative beams)

    f=figure(1);clf;
    nice_plots;
    ha = tight_subplot(3,2,0.07,0.03,0.1);
    cm=gbkry;
    %cax=[-1.5 1.5];
    cax=[-35 0];
    %cax=[-20 0];
    axes(ha(1));
    %plot_hpix(tilebeamew,counts,cax,1,'jet');title([plottitle,' EW']);add_polar_grid([.7 .7 .7]);
    plot_hpix(tilebeamew-refmodelew,counts,cax,1,'jet');title([label,' EW']);add_polar_grid([.7 .7 .7]);
    axes(ha(2));
    plot_hpix(tilebeamns,counts,cax,1,'jet');title([plottitle,' NS']);add_polar_grid([.7 .7 .7]);
    %plot_hpix(tilebeamns-refmodelns,counts,cax,1,'jet');title([label,' NS']);add_polar_grid([.7 .7 .7]);

    % E plane is blue, H plane is red
    axes(ha(3));
    plot(dishmodeltheta,dishmodelaz0,'color',[.15,.9,0]);hold on;
    plot(dishmodeltheta,dishmodelaz90,'color',[.15,.9,0]);
    plot_hpix_model_on_slice(cstdishmodel,32,0,[1,0,.95]);
    plot_hpix_model_on_slice(cstdishmodel,32,pi/2,[1,0,.95]);
    plot_slice_null2(tilebeamew,pi/2,'',nsides,counts,'ew',refmodelboresightgainew,[-80,80],[-35,1],1);% E plane
    axes(ha(3));
    plot_slice_null2(tilebeamew,0,'',nsides,counts,'ew',refmodelboresightgainew,[-80,80],[-35,1],1);% H plane
    %plot(feedmodelslice1za,feedmodelslice1,'b');
    %plot(feedmodelslice2za,feedmodelslice2,'r');

    axes(ha(4));
    plot(dishmodeltheta,dishmodelaz0,'color',[.25,.95,0]);hold on;
    plot(dishmodeltheta,dishmodelaz90,'color',[.25,.95,0]);
    plot_hpix_model_on_slice(cstdishmodel,32,0,[1,0,.95]);
    plot_hpix_model_on_slice(cstdishmodel,32,pi/2,[1,0,.95]);
    plot_slice_null2(tilebeamns,pi/2,'',nsides,counts,'ns',refmodelboresightgainns,[-80,80],[-35,1],1);% E plane
    axes(ha(4));
    plot_slice_null2(tilebeamns,0,'',nsides,counts,'ns',refmodelboresightgainns,[-80,80],[-35,1],1);% H plane
    axes(ha(4));
    %plot(feedmodelslice1za,feedmodelslice1,'r');
    %plot(feedmodelslice2za,feedmodelslice2,'b');
    
    % E plane is blue, H plane is red
    axes(ha(5));
    plot(dishmodeltheta,dishmodelaz0,'color',[.15,.9,0]);hold on;
    plot(dishmodeltheta,dishmodelaz90,'color',[.15,.9,0]);
    plot_hpix_model_on_slice(cstdishmodel,32,0,[1,0,.95]);
    plot_hpix_model_on_slice(cstdishmodel,32,pi/2,[1,0,.95]);
    plot_slice_null2(tilebeamew,pi/2,'',nsides,counts,'ew',refmodelboresightgainew,[-20,20],[-20,1],0);% E plane
    axes(ha(5));
    plot_slice_null2(tilebeamew,0,'',nsides,counts,'ew',refmodelboresightgainew,[-20,20],[-20,1],0);% H plane
    %plot(feedmodelslice1za,feedmodelslice1,'b');
    %plot(feedmodelslice2za,feedmodelslice2,'r');

    axes(ha(6));
    plot(dishmodeltheta,dishmodelaz0,'color',[.25,.95,0]);hold on;
    plot(dishmodeltheta,dishmodelaz90,'color',[.25,.95,0]);
    plot_hpix_model_on_slice(cstdishmodel,32,0,[1,0,.95]);
    plot_hpix_model_on_slice(cstdishmodel,32,pi/2,[1,0,.95]);
    plot_slice_null2(tilebeamns,pi/2,'',nsides,counts,'ns',refmodelboresightgainns,[-20,20],[-20,1],0);% E plane
    axes(ha(6));
    plot_slice_null2(tilebeamns,0,'',nsides,counts,'ns',refmodelboresightgainns,[-20,20],[-20,1],0);% H plane
    axes(ha(6));

    %axes(ha(5));
    %plot_slice2_null2(tilebeamew-refmodelew,pi/2,'',nsides,counts,'ew',refmodelboresightgainew);% E plane
    %plot_slice2_null2(tilebeamew-refmodelew,0,'',nsides,counts,'ew',refmodelboresightgainew);% H plane

    %axes(ha(6));
    %plot_slice2_null2(tilebeamns-refmodelns,pi/2,'',nsides,counts,'ns',refmodelboresightgainns);% E plane
    %plot_slice2_null2(tilebeamns-refmodelns,0,'',nsides,counts,'ns',refmodelboresightgainns);% H plane

    h = get(gcf,'Children');
    uistack(h(6), 'top');
    uistack(h(3), 'top');
    uistack(h(2), 'top');
    uistack(h(5), 'top');
    
    % only for 3 row figures
    uistack(h(4), 'top');
    uistack(h(8), 'top');

    cd('/Users/abrahamn/Documents/MIT/21cm/hera/2015/jul13/unpolarized_beam_analysis_hera');
    set(gcf,'PaperUnits','inches','PaperPosition',[0 0 10 13],'PaperSize',[10 13]);
    print([label,'_abs_old_ref_model','.png'],'-dpng','-r250',f);
    %print([label,'_rel','.png'],'-dpng','-r250',f);
end

%% feed0 debugging

%figure;
%plot_slice_null2(tilebeamew-max(tilebeamew),pi/2,'',nsides,counts,'ew',0);

%figure;
%plot_slice_null2(tilebeamew2-max(tilebeamew2),pi/2,'',nsides,counts,'ew',0);

figure;
scatter(sin(za).*sin(az),sin(za).*cos(az),10,oldrefmodelewdataorder-max(oldrefmodelewdataorder));colorbar;caxis([-5,0]);colormap(gbkry);
title('old ref model');

figure;
scatter(sin(za).*sin(az),sin(za).*cos(az),10,newrefmodelewdataorder-max(newrefmodelewdataorder));colorbar;caxis([-5,0]);colormap(gbkry);
title('new ref model');

%% plot raw powers

g = 1:6:length(refew);
ax2=[-5,15];
ax3=[-2.5,15];

figure(10);
subplot(221);
scatter(sin(za(g)).*sin(az(g)),sin(za(g)).*cos(az(g)),30,refew(g),'filled');
axis square;
colorbar;
xlim([-1,1]);
ylim([-1,1]);
title('refew');
caxis(ax2);

subplot(222);
scatter(sin(za(g)).*sin(az(g)),sin(za(g)).*cos(az(g)),30,tileew(g),'filled');
axis square;
xlim([-1,1]);
ylim([-1,1]);
title('tileew');
colorbar;
caxis(ax3);

subplot(223);
scatter(sin(za(g)).*sin(az(g)),sin(za(g)).*cos(az(g)),30,refns(g),'filled');
axis square;
xlim([-1,1]);
ylim([-1,1]);
title('refns');
colorbar;
caxis(ax2);

subplot(224);
scatter(sin(za(g)).*sin(az(g)),sin(za(g)).*cos(az(g)),30,tilens(g),'filled');
axis square;
xlim([-1,1]);
ylim([-1,1]);
title('tilens');
colorbar;
caxis(ax3);

