
% import a new refpolbeams_snrfilt mapfile

% argument oddeven = 0,1
function [za,az,tileew,refew,tilens,refns,refmodelew,refmodelns,satnum,passnum,hours,pixnums]=import_mapfile2_firstsecondhalf(label,nsides,oddeven)

    disp(['importing ',label,'...']);
    
    root=['/Users/abrahamn/data/21cm/sat_cal/updates/2013/sep1/phase4/',label,'/'];
    mapfilename=['mapfile',label,'_refpolbeams_snrfilt'];
    disp([root,mapfilename]);

    rawdat=importdata([root,mapfilename],' ',19);
    dat=rawdat.data;
    
    overallgain = 40;
    
    n=length(dat(:,1));
    g = find( mod(((1:n)<n/2)+oddeven,2) );
    
    za=dat(g,1)*pi/180;
    az=dat(g,2)*pi/180;
    tileew=dat(g,3)+overallgain;
    refew=dat(g,4)+overallgain;
    tilens=dat(g,5)+overallgain;
    refns=dat(g,6)+overallgain;
    %tileewtot=dat(:,7);
    %refewtot=dat(:,8);
    %tilenstot=dat(:,9);
    %refnstot=dat(:,10);
    refmodelewtheta=dat(g,11);
    refmodelewphi=dat(g,12);
    refmodelnstheta=dat(g,13);
    refmodelnsphi=dat(g,14);
    satnum=dat(g,15);
    passnum=dat(g,16);
    hours=dat(g,17);
    
    refmodelew = 10*log10(10.^(.1*refmodelewphi)+10.^(.1*refmodelewtheta));
    refmodelns = 10*log10(10.^(.1*refmodelnsphi)+10.^(.1*refmodelnstheta));
    
    angarr = arrayfun(@(x,y)([x;y]),za,az,'UniformOutput',false);
    pixnums = ang2pix(nsides,angarr);
    
    disp('done');

end