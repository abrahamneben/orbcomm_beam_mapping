
function A = array_factor_and_ground_screen_power_beam(theta,phi)

    f=137.5e6;
    h=.3;
    lambda=3.e8/f;
    
    A = sin(2*pi*cos(theta)*h/lambda)^2;
end
