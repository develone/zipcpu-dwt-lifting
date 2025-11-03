clear
fid = fopen('g.bin','r'); im1 = fread(fid, [256,inf], 'int32'); fclose(fid);
fid = fopen('dwt.bin','r'); im4 = fread(fid, [256,inf], 'int32'); fclose(fid);
figure;
imagesc(im1);
colorbar;
colormap 'gray';
title "b.bin 11/02/25";
  
figure;
imagesc(im4);
colorbar;
colormap 'gray'
title "DWT  jpeg.c 3 Lvls 11/02/25 write 0x0200fdf8 read 0x0200fdf8";

