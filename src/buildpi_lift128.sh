#/bin/bash
rm -f ../host/pi_jpeg128 lifting.o pi_jpeg128.o
gcc -g -c lifting.c -o lifting.o
gcc -g -c pi_jpeg128.c -o pi_jpeg128.o
gcc -g pi_jpeg128.o lifting.o -o ../host/pi_jpeg128
