obj_files = pi_jpeg.o lifting.o pnmio.o error.o
src_files = pi_jpeg.c lifting.c pnmio.c error.c
CC = gcc

CFLAGS = -c -g -I.  

all: $(obj_files)



clean:
	rm -f *.o  ../host/pi_jpeg

pi_jpeg:
	$(CC) pi_jpeg.o lifting.o pnmio.o error.o -o ../host/pi_jpeg
