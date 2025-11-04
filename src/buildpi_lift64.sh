#/bin/bash
rm -f ../host/pi_jpeg64 lifting.o pi_jpeg64.o
gcc -g -c lifting.c -o lifting.o
gcc -g -c pi_jpeg64.c -o pi_jpeg64.o
gcc -g pi_jpeg64.o lifting.o -o ../host/pi_jpeg64
