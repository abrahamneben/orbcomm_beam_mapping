
function plot_hpix_model_on_slice(hpix_model,nsides,sliceangle,colvec)
    ind1 = [];
    ind2 = [];
    ind1ang = [];
    ind2ang = [];
    dang = .04;
    npix = length(hpix_model);
    counts = ones(length(hpix_model));
    
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
    data = [hpix_model(ind2);hpix_model(ind1)];
    
    plot(xsort,data(xsortind),'color',colvec);hold on;
end