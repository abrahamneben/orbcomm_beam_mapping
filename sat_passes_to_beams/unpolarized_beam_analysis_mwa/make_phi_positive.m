function phi2=make_phi_positive(phi)
    phi2=phi;
    if phi<0
        phi2=phi+2*pi;
    end