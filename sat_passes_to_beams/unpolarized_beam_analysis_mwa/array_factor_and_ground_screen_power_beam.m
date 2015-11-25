
function A = array_factor_and_ground_screen_power_beam(theta,phi,delaybits)

    dipoles = [0 0 0; 1.1  0 0; 2.2 0 0; 3.3 0 0; 0 -1.1 0; 1.1 -1.1 0; 2.2 -1.1 0; 3.3 -1.1 0; 0 -2.2 0; 1.1 -2.2 0; 2.2 -2.2 0; 3.3 -2.2 0; 0 -3.3 0; 1.1 -3.3 0; 2.2 -3.3 0; 3.3 -3.3 0];

    delaydata = zeros(16,32); % ns
    for anti=1:16
       delaydata(anti,:) = (0:31)*0.435;
    end
    
    f=137.5e6;
    h=.3;
    lambda=3.e8/f;
    k = 2*pi/lambda*[sin(theta)*sin(phi) sin(theta)*cos(phi) cos(theta)];
    
    array_factor=0;
    for anti=1:16
        phase = 2*pi*f*delaydata(anti,1+delaybits(anti))*1.e-9;
        array_factor = array_factor + exp(1j*sum(dipoles(anti,:).*k)-1j*phase);
    end
    
    A = sin(2*pi*cos(theta)*h/lambda)^2*abs(array_factor)^2;
end
