fid = fopen('dwt.bin','r'); im4 = fread(fid, [64,inf], 'int32'); fclose(fid);
figure;
imagesc(im4);
colorbar;
colormap 'gray';
