
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lifting.h"
/* First parameter is used to tell the program which sub band to use 
 * 0 Red
 * 1 Green
 * 2 Blue
 * 2nd parameter is used to tell the program to compute the fwd lifting step only or fwd lifting then inv lifting step
 * 0 fwd lifting then inv lifting step
 * 1 fwd lifting step only
 * ./pi_jpeg 0 1 or ./pi_jpeg 0 0
 * ./pi_jpeg 1 1 or ./pi_jpeg 1 0
 * ./pi_jpeg 2 1 or ./pi_jpeg 2 0
 */
struct PTRs {
	char *inpbuf;
	 
	int flag;
	int w;
	int h;
	char *alt;
	//int *fwd_inv;
} ptrs;

char *fff;
int main(int argc, char *argv[]) {
	
	FILE *inptr,*outptr;
	  char *ch;
	  int tmp,loop;
	 
	 int *red_s_ptr, *gr_s_ptr, *bl_s_ptr;
	 char *wptr,*wptr1,*wptr2;
	 int *alt,*alt1,*alt2;
	
	 
	 char *buf;
	 int ur,ug,ub,x,y,z;
	int *fwd_inv;	

	int i,j;
	
	 

	ptrs.w = atoi(argv[1]);
	ptrs.h = atoi(argv[2]);
	//ch = argv[3];
	printf("ptrs.w %d ptrs.h %d \n",ptrs.w,ptrs.h);
    printf("fname %s \n",argv[3]);
		//strncpy(fff, argv[3], sizeof(fff) - 1);
    //printf("address of fname 0x%x \n", &fff);
    
    //return 0;
  tmp = atoi(argv[4]);
  if (tmp == 0) { 
			printf("fwd lifting then inv lifting step\n");
			fwd_inv = tmp;
	}
	else if (tmp == 1) {
			printf("fwd lifting step only\n");
			fwd_inv = tmp;
	}

	
	buf = ( char *)malloc(sizeof( int)* ptrs.w*ptrs.h*2);
	printf("buf = 0x%x\n",buf);
	ptrs.inpbuf = buf;
	printf("ptrs.buf = 0x%x\n",ptrs.inpbuf);
	fwd_inv = (int *)malloc(1);
	printf("fwd_inv = 0x%x\n",fwd_inv);
	 
	printf("reading \n");
	ptrs.flag = tmp;
	inptr = fopen(argv[3],"rb");
	if (!inptr)
	{
		printf("Unle to open file!");
		return 1;
	}
	else 
	{
		fread(ptrs.inpbuf,sizeof(char),4096,inptr);
 
		fclose(inptr);

	}
	loop = 16;
  for(i=0;i<loop;i++)
  {
		printf("0x%x \n",*ptrs.inpbuf);
		ptrs.inpbuf++;
  }
  ptrs.inpbuf = ptrs.inpbuf - loop;
  printf("ptrs.buf = 0x%x\n",ptrs.inpbuf);
  wptr = ptrs.inpbuf;
	printf("wptr = 0x%x\n",wptr);
	ptrs.alt = &buf[ptrs.w*ptrs.h];
	printf("ptrs.alt = 0x%x\n",ptrs.alt);
	printf("starting dwt\n");
  
	lifting(ptrs.w,wptr,ptrs.alt,fwd_inv);
	printf("finished ted dwt\n");
		//pack(ptrs.flag, i,buf_red, ptrs.inpbuf);
	
    outptr = fopen("dwt.bin","wb");
  if (!outptr)
	{
 	printf("Unle to open file!");
	return 1;
	}
	fwrite(ptrs.inpbuf,sizeof( char),4096,outptr);
	//fwrite(alt,sizeof( int),65536,outptr);
	fclose(outptr);
  
	return 0;

}
