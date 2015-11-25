
function [tilebeamew,tilebeamns,tilebeamewstd,tilebeamnsstd,tilebeamnumpasses,modeltilebeamew,modeltilebeamns,counts,outliers,refpowhpixew,refpowhpixns,refmodelhpixewlin,refmodelhpixnslin]=make_tilebeams(tileew,refew,tilens,refns,refmodelew,refmodelns,pixnums,nsides,delaynums,passnum,satnum)

    disp('making tile beams...');
    npix = nSide2nPix(nsides);
    tilebeamew = zeros(npix,1);
    tilebeamns = zeros(npix,1);
    tilebeamewstd = zeros(npix,1);
    tilebeamnsstd = zeros(npix,1);
    modeltilebeamew = zeros(npix,1);
    modeltilebeamns = zeros(npix,1);
    tilebeamnumpasses = zeros(npix,1);
    counts = zeros(npix,1);
    outliers = zeros(npix,1);
    refpowhpixew = zeros(npix,1);
    refpowhpixns = zeros(npix,1);
    refmodelhpixewlin = zeros(npix,1);
    refmodelhpixnslin = zeros(npix,1);
    
    for pixi=1:npix
        ang = pix2ang(nsides,pixi);
        pixza = ang{1}(1);
        pixaz = ang{1}(2);

        modeltilebeamew(pixi) = (1-sin(pixza)^2*sin(pixaz)^2)*array_factor_and_ground_screen_power_beam(pixza,pixaz,delaynums);
        modeltilebeamns(pixi) = (1-sin(pixza)^2*cos(pixaz)^2)*array_factor_and_ground_screen_power_beam(pixza,pixaz,delaynums);

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
        
%         if mod(pixi,20)==0
%             figure;
%             hist(pixeldatans,linspace(0,max(pixeldatans),100));xlim([0 100]);pause(1);
%         end

        refpowhpixew(pixi) = mean(purge_outliers(10.^(.1*refew(ind))));
        refpowhpixns(pixi) = mean(purge_outliers(10.^(.1*refns(ind))));
        refmodelhpixewlin(pixi) = mean(10.^(.1*refmodelew(ind)));
        refmodelhpixnslin(pixi) = mean(10.^(.1*refmodelns(ind)));
        
        %tilebeamew(pixi) = 10*log10(mean(pixeldataew));
        %tilebeamns(pixi) = 10*log10(mean(pixeldatans));
        tilebeamew(pixi) = mean(pixeldataew);
        tilebeamns(pixi) = mean(pixeldatans);
        
        tilebeamewstd(pixi) = std(pixeldataew);
        tilebeamnsstd(pixi) = std(pixeldatans);
        tilebeamnumpasses(pixi) = length(unique(passnum(ind).*satnum(ind)));
        
        if pixi==12
            disp(tilebeamew(12));
        end
    end

    disp('done');

end



