function [tilebeamew,tilebeamns,counts,tilebeamnumpasses,outliers]=make_tilebeams_null2(tileew,refew,tilens,refns,refmodelew,refmodelns,pixnums,nsides,passnum,satnum)

    disp('making tile beams...');
    npix = nSide2nPix(nsides);
    tilebeamew = zeros(npix,1);
    tilebeamns = zeros(npix,1);
    modeltilebeamew = zeros(npix,1);
    modeltilebeamns = zeros(npix,1);
    counts = zeros(npix,1);
    tilebeamnumpasses = zeros(npix,1);
    outliers = zeros(npix,1);
    
    for pixi=1:npix
        ang = pix2ang(nsides,pixi);
        pixza = ang{1}(1);
        pixaz = ang{1}(2);

        ind = find(pixnums==pixi);
        n = length(ind);
        if n<2
            continue;
        end
        if mod(pixi,1000)==0
            fprintf('pixi=%d/%d\n',pixi,npix);
        end
        counts(pixi) = n;
        
        pixeldataew = purge_outliers(10.^(.1*(tileew(ind)-refew(ind)+refmodelew(ind))));
        pixeldatans = purge_outliers(10.^(.1*(tilens(ind)-refns(ind)+refmodelns(ind))));
        outliers(pixi) = n - min(length(pixeldataew),length(pixeldatans));

        tilebeamew(pixi) = average_excluding_outliers(tileew(ind)-refew(ind)+refmodelew(ind));
        tilebeamns(pixi) = average_excluding_outliers(tilens(ind)-refns(ind)+refmodelns(ind));
        
        tilebeamnumpasses(pixi) = length(unique(passnum(ind).*satnum(ind)));
        
    end

    disp('done');

end



