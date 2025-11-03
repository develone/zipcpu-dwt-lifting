#/bin/bash
rm -f ../host/pi_jpeg lifting.o pi_jpeg.o
aarch64-linux-gnu-gcc -g -c lifting.c -o lifting.o
aarch64-linux-gnu-gcc -g -c pi_jpeg.c -o pi_jpeg.o
aarch64-linux-gnu-gcc -g pi_jpeg.o lifting.o -o ../host/pi_jpeg
