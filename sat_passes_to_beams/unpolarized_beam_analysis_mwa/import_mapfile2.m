
% import a new refpolbeams_snrfilt mapfile

function [za,az,tileew,refew,tilens,refns,refmodelew,refmodelns,satnum,passnum,hours,pixnums]=import_mapfile2(label,nsides)

    disp(['importing ',label,'...']);
    
    root=['/Users/abrahamn/data/21cm/sat_cal/updates/2013/sep1/phase4/',label,'/'];
    mapfilename=['mapfile',label,'_refpolbeams_snrfilt'];
    disp([root,mapfilename]);

    rawdat=importdata([root,mapfilename],' ',19);
    dat=rawdat.data;
    
    overallgain = 40;
    
    za=dat(:,1)*pi/180;
    az=dat(:,2)*pi/180;
    tileew=dat(:,3)+overallgain;
    refew=dat(:,4)+overallgain;
    tilens=dat(:,5)+overallgain;
    refns=dat(:,6)+overallgain;
    %tileewtot=dat(:,7);
    %refewtot=dat(:,8);
    %tilenstot=dat(:,9);
    %refnstot=dat(:,10);
    refmodelewtheta=dat(:,11);
    refmodelewphi=dat(:,12);
    refmodelnstheta=dat(:,13);
    refmodelnsphi=dat(:,14);
    satnum=dat(:,15);
    passnum=dat(:,16);
    hours=dat(:,17);
    
    refmodelew = 10*log10(10.^(.1*refmodelewphi)+10.^(.1*refmodelewtheta));
    refmodelns = 10*log10(10.^(.1*refmodelnsphi)+10.^(.1*refmodelnstheta));
    
    angarr = arrayfun(@(x,y)([x;y]),za,az,'UniformOutput',false);
    pixnums = ang2pix(nsides,angarr);
    
    disp('done');

end