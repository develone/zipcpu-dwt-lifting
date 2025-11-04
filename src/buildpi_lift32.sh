#/bin/bash
rm -f ../host/pi_jpeg64 lifting.o pi_jpeg64.o
gcc -g -c lifting.c -o lifting.o
gcc -g -c pi_jpeg32.c -o pi_jpeg32.o
gcc -g pi_jpeg32.o lifting.o -o ../host/pi_jpeg32
