% plot the upper hemisphere of a healpix pixelization of a sphere,
%  using the matlab function patches to plot each healpixel

function plot_hpix(hmap,hmap_counts,cax,showcolorbar,colormapname)
    npix = length(hmap);
    nsides = nPix2nSide(npix);
    
    c_raw=corners(nsides);
    c=zeros(npix,3,4);

    for pixi=1:npix
        c(pixi,:,:) = c_raw{pixi};
    end

    g=ones(npix,1);
    for pixi=1:npix
        z=squeeze(c(pixi,3,:));
        if any(z<0) || hmap_counts(pixi)==0
            g(pixi)=0;
        end
    end
    gg=find(g);


    x=squeeze(c(gg,1,:));
    y=squeeze(c(gg,2,:));
    z=squeeze(c(gg,3,:));

    theta=acos(z)*180/pi;
    phi=atan2(y,x);

    %X=theta.*cos(phi);
    %Y=theta.*sin(phi);
    X=sin(theta*pi/180).*sin(phi);
    Y=sin(theta*pi/180).*cos(phi);

    p=patch(X',Y',zeros(length(gg),4)');
    freezeColors;
    %colorbar;
    clear cdata ;
    set(gca,'CLim',cax);
    set(p,'FaceColor','flat','CData',hmap(gg)','CDataMapping','scaled');
    set(p,'EdgeAlpha',0);
    
    colormap(colormapname);axis square;%add_polar_grid;

    if showcolorbar==1
        cbfreeze(colorbar);
    end
    
    %xlim([-90 90]);
    %ylim([-90 90]);
    xlim([-1 1]);
    ylim([-1 1]);

end

