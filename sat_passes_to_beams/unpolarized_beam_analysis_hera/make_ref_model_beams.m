function [refmodelew,refmodelns] = make_ref_model_beams(nsides)
    disp('making ref model beams...');
    npix = nSide2nPix(nsides);
    oldrefmodelew = zeros(npix,1);
    oldrefmodelns = zeros(npix,1);
    newrefmodelew = zeros(npix,1);
    newrefmodelns = zeros(npix,1);
    
    d='/Users/abrahamn/Documents/MIT/21cm/sat_cal/updates/satcalanalysis/refModel/';
    %refmodelnsdata = importdata([d,'ff137_5_xpol+el.txt']);
    oldrefmodelnsdata = importdata([d,'ff137_5_xpol+el.txt']);
    newrefmodelnsdata = importdata([d,'new_ref_dipole_model_137_31july2015+el.txt']);
    
    angarr = arrayfun(@(x,y)([x;y]),oldrefmodelnsdata(:,1)*pi/180.,mod(oldrefmodelnsdata(:,2)+90,360)*pi/180.,'UniformOutput',false);
    pixnums = ang2pix(nsides,angarr);
    oldrefmodelew(pixnums) = oldrefmodelnsdata(:,3);
    
    angarr = arrayfun(@(x,y)([x;y]),oldrefmodelnsdata(:,1)*pi/180.,oldrefmodelnsdata(:,2)*pi/180.,'UniformOutput',false);
    pixnums = ang2pix(nsides,angarr);
    oldrefmodelns(pixnums) = oldrefmodelnsdata(:,3);
    
    angarr = arrayfun(@(x,y)([x;y]),newrefmodelnsdata(:,1)*pi/180.,mod(newrefmodelnsdata(:,2)+90,360)*pi/180.,'UniformOutput',false);
    pixnums = ang2pix(nsides,angarr);
    newrefmodelew(pixnums) = newrefmodelnsdata(:,3);
    
    angarr = arrayfun(@(x,y)([x;y]),newrefmodelnsdata(:,1)*pi/180.,newrefmodelnsdata(:,2)*pi/180.,'UniformOutput',false);
    pixnums = ang2pix(nsides,angarr);
    newrefmodelns(pixnums) = newrefmodelnsdata(:,3);
    
    %refmodelew = newrefmodelew;
    %refmodelns = newrefmodelns;
    refmodelew = oldrefmodelew;
    refmodelns = oldrefmodelns;
    
    disp('done');
    
end

