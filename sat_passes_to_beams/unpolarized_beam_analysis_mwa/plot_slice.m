function plot_slice(tiledata,sliceangle,plottitle,nsides,maxewind,counts,pol,tilemodelboresightgain,delaynums) % pol is 'ew' or 'ns'
    npix = length(tiledata);
    
    angmax = cell2mat(pix2ang(nsides,maxewind));
    Theta=-angmax(1);
    Phi=pi-angmax(2);

    R=[cos(Theta)+cos(Phi)^2*(1-cos(Theta)), cos(Phi)*sin(Phi)*(1-cos(Theta)), sin(Phi)*sin(Theta);...
        cos(Phi)*sin(Phi)*(1-cos(Theta)), cos(Theta)+sin(Phi)^2*(1-cos(Theta)), -cos(Phi)*sin(Theta);...
        -sin(Phi)*sin(Theta), cos(Phi)*sin(Theta), cos(Theta)];
    
    Theta=angmax(1);
    Rinv=[cos(Theta)+cos(Phi)^2*(1-cos(Theta)), cos(Phi)*sin(Phi)*(1-cos(Theta)), sin(Phi)*sin(Theta);...
        cos(Phi)*sin(Phi)*(1-cos(Theta)), cos(Theta)+sin(Phi)^2*(1-cos(Theta)), -cos(Phi)*sin(Theta);...
        -sin(Phi)*sin(Theta), cos(Phi)*sin(Theta), cos(Theta)];
    
    ind1 = [];
    ind2 = [];
    ind1angrot = [];
    ind2angrot = [];
    dang = .04;
    for pixi=1:npix
        ang=cell2mat(pix2ang(nsides,pixi));
        xyzrot = R*[sin(ang(1))*sin(ang(2));sin(ang(1))*cos(ang(2));cos(ang(1))];
        angrot = [atan(norm(xyzrot(1:2))/xyzrot(3)),make_phi_positive(atan2(xyzrot(1),xyzrot(2)))];
        if (sliceangle==0)&&(abs(angrot(2))<.5*dang/sin(angrot(1)) || abs(angrot(2))>2*pi-.5*dang/sin(angrot(1))) && counts(pixi)>0
            ind1 = [ind1;pixi];
            ind1angrot = [ind1angrot;angrot];
        elseif abs(angrot(2)-sliceangle)<dang/sin(angrot(1)) && counts(pixi)>0
            ind1 = [ind1;pixi];
            ind1angrot = [ind1angrot;angrot];
        elseif abs(angrot(2)-(sliceangle+pi))<dang/sin(angrot(1)) && counts(pixi)>0
            ind2 = [ind2;pixi];
            ind2angrot = [ind2angrot;angrot];
        end 
    end
    
    %evaluate model on slice
    modelza = [-fliplr(linspace(0,pi/2,50)),linspace(0,pi/2,50)];
    modelaz = [zeros(1,50)+sliceangle+pi,zeros(1,50)+sliceangle];
    modelangrot = zeros(length(modelza),2);
    for i=1:length(modelza)
        xyzrot = Rinv*[sin(abs(modelza(i)))*sin(modelaz(i));sin(abs(modelza(i)))*cos(modelaz(i));cos(abs(modelza(i)))];
        modelangrot(i,:) = [atan(norm(xyzrot(1:2))/xyzrot(3)),make_phi_positive(atan2(xyzrot(1),xyzrot(2)))];
    end
    model = make_tile_model_slice_beam(modelangrot(:,1),modelangrot(:,2),pol,tilemodelboresightgain,delaynums);
    disp(tilemodelboresightgain);
    
    x=[-ind2angrot(:,1);ind1angrot(:,1)]*180/pi;
    [xsort,xsortind] = sort(x);
    
    data = [tiledata(ind2);tiledata(ind1)];
    
    col = 'r';
    colval = .5;
    if (strcmp(pol,'ew')&&(sliceangle==pi/2))||(strcmp(pol,'ns')&&(sliceangle==0))
        col = 'b';
        colval = -.5;
    end
    
    insetx = .35;
    if strcmp(pol,'ew')
        insetx = .78;
    end
    
    nice_plots;
    %f=figure(1);clf;
    set(0,'defaultLineLineWidth',1);
    plot(xsort,data(xsortind),[col,'.'],'MarkerSize',14);hold on;
    %plot(modelza*180/pi,10.^(.1*model),'k-');
    plot(modelza*180/pi,model,[col,'-']);
    plot(-23./2+[.001,.0011],[-40,30],'k:',23./2+[.001,.0011],[-40,30],'k:');
    title(plottitle);xlim([-80 80]);ylim([-35 2.5]);
    set(gca,'XTick',[-80:20:80]);
    xlabel('\theta');
    ylabel('dB','rot',0);
    set(gca,'linewidth',3);
    
    counts=zeros(npix);
    counts(ind1) = 1;
    counts(ind2) = 1;
    axes('Position',[insetx .51 .1 .1]);
    add_polar_grid([.7 .7 .7]);
    plot_hpix(zeros(npix,1)+colval,counts,[-1,1],0,gbkry);
    

    hold on;
    
end