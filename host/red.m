clear
fid = fopen('red-64','r'); im1 = fread(fid, [64,inf], 'int8'); fclose(fid);
figure;
imagesc(im1);
colorbar;
colormap 'gray';
title 'red-64 06/24/26'
