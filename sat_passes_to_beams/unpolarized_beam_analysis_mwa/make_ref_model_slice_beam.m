function model = make_ref_model_slice_beam(za,az,pol,tilemodelboresightgain)

    model = zeros(length(za),1);
    
    phioffset = 0;
    if strcmp(pol,'ns')
        phioffset = pi/2;
    end
    
    for i=1:length(za)
        model(i) = 10*log10((1-sin(za(i))^2*sin(az(i)+phioffset)^2)*ground_screen_power_beam(za(i),az(i)));
    end
    
    model = model - tilemodelboresightgain;
end