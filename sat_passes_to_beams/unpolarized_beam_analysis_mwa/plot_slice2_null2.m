function plot_slice2_null2(tiledata,sliceangle,plottitle,nsides,counts,pol,refmodelboresightgain) % pol is 'ew' or 'ns'
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

    x=[-ind2ang(:,1);ind1ang(:,1)]*180/pi;
    [xsort,xsortind] = sort(x);
    data = [tiledata(ind2);tiledata(ind1)];
    
    col = 'r';
    if (strcmp(pol,'ew')&&(sliceangle==pi/2))||(strcmp(pol,'ns')&&(sliceangle==0))
        col = 'b';
    end
    
    nice_plots;
    %f=figure(1);clf;
    set(0,'defaultLineLineWidth',1);
    plot(xsort,data(xsortind),[col,'.'],[-100 100],[0 0],'k-','MarkerSize',12);hold on;
    title(plottitle);xlim([-90 90]);ylim([-2.5 3.5]);
    xlabel('\theta');
    ylabel('dB','rot',0);
    set(gca,'linewidth',3);
    set(gca,'XTick',[-80:20:80]);
    
end