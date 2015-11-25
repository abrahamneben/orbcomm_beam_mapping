function plot_slice_polar(tiledata,sliceangle,plottitle,nsides,maxewind,counts,pol,tilemodelboresightgain,delaynums) % pol is 'ew' or 'ns'
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
    g=polar(modelza+pi/2,model'+30,[col,'-']);hold on;
    otherlines = findall(gcf,'type','line');otherlines(otherlines==g)=[];
    delete(otherlines);
    
    h=polar(xsort*pi/180+pi/2,data(xsortind)+30,[col,'o']);
    set( findobj(g, 'Type', 'line'), 'MarkerSize',6,'markerfacecolor',col,'markerfacecolor',col);
    polar([pi/2,pi/2],[0 30],'k--');
    polar(pi/2+20*pi/180*[-1,-1],[0 30],'k--');
    polar(pi/2+40*pi/180*[-1,-1],[0 30],'k--');
    polar(pi/2+60*pi/180*[-1,-1],[0 30],'k--');
   % polar(pi/2+80*pi/180*[-1,-1],[0 30],'k--');
    polar(pi/2+20*pi/180*[1,1],[0 30],'k--');
    polar(pi/2+40*pi/180*[1,1],[0 30],'k--');
    polar(pi/2+60*pi/180*[1,1],[0 30],'k--');
    %polar(pi/2+80*pi/180*[1,1],[0 30],'k--');
    polar(linspace(pi/2-60*pi/180.,pi/2+60*pi/180),zeros(1,100)+30,'k--');
    polar(linspace(pi/2-60*pi/180.,pi/2+60*pi/180),zeros(1,100)+20,'k--');
    polar(linspace(pi/2-60*pi/180.,pi/2+60*pi/180),zeros(1,100)+10,'k--');
    
    ylim([-30 30]);xlim([-30 30]);
    axis square;
    %xlabel('\theta');
    %ylabel('dB','rot',0);
    set( findobj(g, 'Type', 'line'), 'LineWidth',3);
    delete(findall(gcf,'type','text'));
    
    
%     counts=zeros(npix);
%     counts(ind1) = 1;
%     counts(ind2) = 1;
%     axes('Position',[insetx .51 .1 .1]);
%     add_polar_grid([.7 .7 .7]);
%     plot_hpix(zeros(npix,1)+colval,counts,[-1,1],0,gbkry);
    

    hold on;
    
end