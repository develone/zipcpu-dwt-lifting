obj_files = pi_jpeg.o lifting.o
src_files = pi_jpeg.c lifting.c
CC = gcc

CFLAGS = -c -g -I.  

all: $(obj_files)



clean:
	rm -f *.o  ../host/pi_jpeg

pi_jpeg:
	$(CC) pi_jpeg.o lifting.o -o ../host/pi_jpeg
