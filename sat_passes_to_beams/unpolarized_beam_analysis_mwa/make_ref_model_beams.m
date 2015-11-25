function [refmodelew,refmodelns] = make_ref_model_beams(nsides)
    disp('making ref model beams...');
    npix = nSide2nPix(nsides);
    refmodelew = zeros(npix,1);
    refmodelns = zeros(npix,1);
    
    d='/Users/abrahamn/Documents/MIT/21cm/sat_cal/updates/satcalanalysis/refModel/';
    refmodelnsdata = importdata([d,'ff137_5_xpol+el.txt']);
    refmodelewdata = importdata([d,'ff137_5_ypol+el.txt']);
    
    angarr = arrayfun(@(x,y)([x;y]),refmodelnsdata(:,1)*pi/180.,refmodelnsdata(:,2)*pi/180.,'UniformOutput',false);
    pixnums = ang2pix(nsides,angarr);
    
    refmodelew(pixnums) = refmodelewdata(:,3);
    refmodelns(pixnums) = refmodelnsdata(:,3);
    disp('done');
    
end

