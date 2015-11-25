function add_polar_grid(rgbcolor)

    hold on;
    
    theta = linspace(0,2*pi,50);
    for za=[20,40,60,80]
        set(0,'defaultLineLineWidth',2);
       p=polar(theta,ones(1,50)*sin(za*pi/180),'--');axis square;axis off;
       set(p,'color',rgbcolor);
    end
    
    %text(0,100, 'N', 'Color', 'k');
    %text(100, 0, 'E', 'Color', 'k');
    %text(0, -100-5, 'S', 'Color', 'k');
    %text(-100-15, 0, 'W', 'Color', 'k');

end