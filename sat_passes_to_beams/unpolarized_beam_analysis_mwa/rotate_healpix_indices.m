
% THIS FUNCTION HAS BEEN DEPRECATED

function rotpixindices = rotate_healpix_indices(nsides,pixindices,Theta,Phi)

    R=[cos(Theta)+cos(Phi)^2*(1-cos(Theta)), cos(Phi)*sin(Phi)*(1-cos(Theta)), sin(Phi)*sin(Theta);...
        cos(Phi)*sin(Phi)*(1-cos(Theta)), cos(Theta)+sin(Phi)^2*(1-cos(Theta)), -cos(Phi)*sin(Theta);...
        -sin(Phi)*sin(Theta), cos(Phi)*sin(Theta), cos(Theta)];
    
    rotpixindices = zeros(length(pixindices),1);
    for pixindi=1:length(pixindices)
        pixi=pixindices(pixindi);
        ang=cell2mat(pix2ang(nsides,pixi));
        xyzrot = R*[sin(ang(1))*sin(ang(2));sin(ang(1))*cos(ang(2));cos(ang(1))];
        angrot = [atan(norm(xyzrot(1:2))/xyzrot(3)),atan2(xyzrot(1),xyzrot(2))];
        rotpixindices(pixindi) = ang2pix(nsides,{angrot});
    end

end