
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
	 
	short int flag;
	short int w;
	short int h;
	short int *alt;
	//short int *fwd_inv;
} ptrs;

char *fff;
int main(int argc, char *argv[]) {
	
	FILE *inptr,*outptr;
	  char *ch;
	  short int tmp,loop;
	 
	 short int *red_s_ptr, *gr_s_ptr, *bl_s_ptr;
	 short int *wptr,*wptr1,*wptr2;
	 short int *alt,*alt1,*alt2;
	
	 
	 char *buf;
	 short int ur,ug,ub,x,y,z;
	short int *fwd_inv;	

	short int i,j;
	
	 

	ptrs.w = atoi(argv[1]);
	ptrs.h = atoi(argv[2]);
	//ch = argv[3];
	printf("ptrs.w %d ptrs.h %d \n",ptrs.w,ptrs.h);
    printf("fname %s \n",argv[3]);
		//strncpy(fff, argv[3], sizeof(fff) - 1);
    //printf("address of fname 0x%x \n", &fff);
    
    //return 0;
	fwd_inv = (short int *)malloc(1);
	printf("fwd_inv = 0x%x\n",fwd_inv);
	tmp = atoi(argv[4]);
	if (tmp == 0) 
	{ 
			
		*fwd_inv = (short int) tmp;
		printf("fwd lifting then inv lifting step  %d *fwd_inv 0x%x \n",*fwd_inv,fwd_inv);
	}
	else if (tmp == 1) 
	{
			
		*fwd_inv = (short int) tmp;
		printf("fwd lifting step only 0x%x *fwd_inv %d \n",*fwd_inv,fwd_inv);
	}

	buf = ( char *)malloc(sizeof( char)* ptrs.w*ptrs.h);
	printf("buf = 0x%x\n",buf);
	
	ptrs.inpbuf = ( short int *)malloc(sizeof( short int)* ptrs.w*ptrs.h*2);
	printf("ptrs.inpbuf = 0x%x\n",ptrs.inpbuf);
	//ptrs.inpbuf = buf;
	//printf("ptrs.buf = 0x%x\n",ptrs.inpbuf);
	
	 
	//loop = ptrs.w*ptrs.h;
    	//for(i=0;i<loop;i++)	
	printf("reading \n");
	ptrs.flag = tmp; 
	inptr = fopen(fname,"rb");
	printf("inptr %d \n",inptr);
	if(!inptr)
	{
		printf("Unable to open file!");
		return 1;
	}
	else 
	{
		
		loop = fread(buf,sizeof(char),ptrs.w*ptrs.h,inptr);
        	printf("number of char %d\n",loop);
		//fclose(inptr);

	}

    { 
		*ptrs.inpbuf = *buf;
		printf("0x%x 0x%x\n",*buf,*ptrs.inpbuf);
		buf++;
		ptrs.inpbuf++;
    }
    free(buf);
    //buf = buf - loop;
    ptrs.inpbuf = ptrs.inpbuf - loop;
    printf("ptrs.buf = 0x%x\n",ptrs.inpbuf);
    wptr = (short int)ptrs.inpbuf;
	printf("wptr = 0x%x\n",wptr);
	ptrs.alt = &buf[ptrs.w*ptrs.h];
	printf("ptrs.alt = 0x%x\n",ptrs.alt);
	printf("starting dwt\n");
  
	lifting(ptrs.w,wptr,ptrs.alt,fwd_inv);
	printf("finished dwt\n");
		//pack(ptrs.flag, i,buf_red, ptrs.inpbuf);
	
    outptr = fopen("dwt.bin","wb");
	if (!outptr)
	{
		printf("Unle to open file!");
		return 1;
	}
	else fwrite(ptrs.inpbuf,sizeof( char),ptrs.w*ptrs.h,outptr);
	//fwrite(alt,sizeof( short int),65536,outptr);
	fclose(outptr);
	 
	free(ptrs.inpbuf);
	return 0;

}
