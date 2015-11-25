
% import a new refpolbeams_snrfilt mapfile

%function [za,az,tileew,refew,tilens,refns,oldrefmodelew,oldrefmodelns,newrefmodelew,newrefmodelns,satnum,passnum,hours,pixnums]=import_mapfile2_null(nsides,label)
function [za,az,tileew,refew,tilens,refns,refmodelew,refmodelns,satnum,passnum,hours,pixnums]=import_mapfile2_null(nsides,label)

    disp(['importing',label,'...']);

    %/Users/abrahamn/data/21cm/hera/2015/jul13/null0/mapfilenull0_EW.csv
    root=['/Users/abrahamn/data/21cm/hera/2015/jul13/',label,'/'];
    mapfilename=['mapfile',label,'_refpolbeams_snrfilt'];
    %mapfilename=['mapfile',label,'_snrfilt_add_old_new_refmodel'];
    disp([root,mapfilename]);

    rawdat=importdata([root,mapfilename]);
    dat=rawdat.data;
    
    overallgain = 40;
    
    
    if length(strfind(label,'null'))==1
        fprintf('using null experimnent input ordering\n');
        % tile refers to the north ref ant
        % ref refers to the south ref ant
        
        %Ch 1 - N/S dipole on the south end of the line. 
        %Ch 2 - N/S dipole on the north end of the line. 
        %Ch 3 is E/W dipole on the south end of the line. 
        %Ch 4 is the E/W dipole on the north end of the line.
        refnscol = 1;
        tilenscol = 2;
        refewcol = 3;
        tileewcol = 4;
    else
        fprintf('using feed/dish experiment input ordering\n');
        % tile refers to the feed 
        % ref refers to the ref ant
        
        %The configuration is the same as what you had with the drone. We simply removed the attenuators. The PAPER feed replaced the south dipoles.
        %For the octocopter experiment we had the antennas connected as
        %1 - S ant, NS-oriented dipole
        %2 - N ant, NS-oriented dipole
        %3 - S ant, EW-oriented dipole
        %4 - N ant, EW-oriented dipole
        tilenscol = 1;
        refnscol = 2;
        tileewcol = 3;
        refewcol = 4;
    end
    
    za=dat(:,1)*pi/180;
    az=dat(:,2)*pi/180;
    tileew=dat(:,2+tileewcol)+overallgain;
    refew=dat(:,2+refewcol)+overallgain;
    tilens=dat(:,2+tilenscol)+overallgain;
    refns=dat(:,2+refnscol)+overallgain;
    %tileewtot=dat(:,7);
    %refewtot=dat(:,8);
    %tilenstot=dat(:,9);
    %refnstot=dat(:,10);
    refmodelewtheta=dat(:,11);
    refmodelewphi=dat(:,12);
    refmodelnstheta=dat(:,13);
    refmodelnsphi=dat(:,14);
    %oldrefmodelew=dat(:,11);
    %oldrefmodelns=dat(:,12);
    %newrefmodelew=dat(:,13);
    %newrefmodelns=dat(:,14);
    satnum=dat(:,15);
    passnum=dat(:,16);
    hours=dat(:,17);
    
    %refmodelew = oldrefmodelew;
    %refmodelns = oldrefmodelns;
    refmodelew = 10*log10(10.^(.1*refmodelewphi)+10.^(.1*refmodelewtheta));
    refmodelns = 10*log10(10.^(.1*refmodelnsphi)+10.^(.1*refmodelnstheta));
    
    angarr = arrayfun(@(x,y)([x;y]),za,az,'UniformOutput',false);
    pixnums = ang2pix(nsides,angarr);
    
    disp('done');

end