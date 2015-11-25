function plot_slice2_noisestudy(tiledata,sliceangle,plottitle,nsides,xlabelstr,counts,pol,col,cax) % pol is 'ew' or 'ns'
    npix = length(tiledata);
    
    angmax = cell2mat(pix2ang(nsides,1));
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

    x=[-ind2angrot(:,1);ind1angrot(:,1)]*180/pi;
    [xsort,xsortind] = sort(x);
    
    data = [tiledata(ind2);tiledata(ind1)];
    
    nice_plots;
    %f=figure(1);clf;
%    set(0,'defaultLineLineWidth',1);
    plot(xsort,data(xsortind),[col,'-'],[-100 100],[0 0],'k','MarkerSize',14);hold on;
    plot(-23./2+[.001,.0011],[-30,30],'k:',23./2+[.001,.0011],[-30,30],'k:');
    title(plottitle);xlim([-80 80]);ylim(cax);
    set(gca,'XMinorTick','on','YMinorTick','on');
    set(gca,'XTick',[-80:20:80]);
    xlabel('\theta');
    ylabel(xlabelstr,'rot',0);
    set(gca,'linewidth',3);
    
    %counts=zeros(npix);
    %counts(ind1) = 1;
    %counts(ind2) = 1;
    %axes('Position',[.7 .7 .2 .2]);
    %box on;
    %%%%%plot_hpix(tiledata-10,ones(npix,1),[-30,5],1,jet);
    %plot_hpix(zeros(npix,1)-1,counts,[-1,0],0,gray);
    %add_polar_grid([.2 .2 .2]);
    
    %set(gcf,'PaperUnits','inches','PaperPosition',[0 0 5 5]);
    %set(gca,'FontSize',12,'FontWeight','bold','linewidth',2);
    %print([strrep(plottitle,' ','_'),'.png'],'-dpng', '-r100',f);
    
    hold on;
    
end