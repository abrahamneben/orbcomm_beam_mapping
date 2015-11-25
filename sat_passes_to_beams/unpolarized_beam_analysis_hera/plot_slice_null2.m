function plot_slice_null2(tiledata,sliceangle,plottitle,nsides,counts,pol,refmodelboresightgain,xlimits,ylimits,showinset) % pol is 'ew' or 'ns'
    npix = length(tiledata);
    
    ind1 = [];
    ind2 = [];
    ind1ang = [];
    ind2ang = [];
    dang = .04;
    for pixi=1:npix
        ang=cell2mat(pix2ang(nsides,pixi))';
        if (sliceangle==0)&&(abs(ang(2))<.5*dang/sin(ang(1)) || abs(ang(2))>2*pi-.5*dang/sin(ang(1))) && counts(pixi)>0
            ind1 = [ind1;pixi];
            ind1ang = [ind1ang;ang];
        elseif abs(ang(2)-sliceangle)<dang/sin(ang(1)) && counts(pixi)>0
            ind1 = [ind1;pixi];
            ind1ang = [ind1ang;ang];
        elseif abs(ang(2)-(sliceangle+pi))<dang/sin(ang(1)) && counts(pixi)>0
            ind2 = [ind2;pixi];
            ind2ang = [ind2ang;ang];
        end 
    end
    
    %evaluate model on slice
    d='/Users/abrahamn/Documents/MIT/21cm/sat_cal/updates/satcalanalysis/refModel/';
    if strcmp(pol,'ew')
        refmodeldata = importdata([d,'ff137_5_ypol+el.txt']);
    else
        refmodeldata = importdata([d,'ff137_5_xpol+el.txt']);
    end
    sliceangledeg = round(sliceangle*180/pi);
    onslice1=find(refmodeldata(:,2)==sliceangledeg);
    onslice2=find(refmodeldata(:,2)==sliceangledeg+180);
    modelza = [-refmodeldata(onslice2,1);refmodeldata(onslice2,1)];
    model = [refmodeldata(onslice2,3);refmodeldata(onslice1,3)]-refmodelboresightgain;
    [modelzasort,modelzasortind] = sort(modelza);
    
    x=[-ind2ang(:,1);ind1ang(:,1)]*180/pi;
    [xsort,xsortind] = sort(x);
    data = [tiledata(ind2);tiledata(ind1)];
    
    col = 'r';
    colval = .5;
    if (strcmp(pol,'ew')&&(sliceangle==pi/2))||(strcmp(pol,'ns')&&(sliceangle==0))
        col = 'b';
        colval = -.5;
    end
    disp(col);
    
    nice_plots;
    set(0,'defaultLineLineWidth',1);
    plot(xsort,data(xsortind),[col,'.'],'MarkerSize',14);hold on;
    %plot(modelzasort,model(modelzasortind),[col,'-']);
    title(plottitle);xlim(xlimits);ylim(ylimits);
    xlabel('\theta');
    ylabel('dB','rot',0);
    set(gca,'linewidth',3);
    set(gca,'XTick',[-80:20:80]);
    grid on;
    
    insetx = .35;
    if strcmp(pol,'ns')
        insetx = .78;
    end
    
    if showinset==1
        counts=zeros(npix);
        counts(ind1) = 1;
        counts(ind2) = 1;
        axes('Position',[insetx .52 .1 .1]);
        %axes('Position',[insetx .35 .1 .1]);
        add_polar_grid([.7 .7 .7]);
        plot_hpix(zeros(npix,1)+colval,counts,[-.75,.75],0,jet);
    end
   
    
end