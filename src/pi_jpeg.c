
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
	 int inpbuf[8192];
	 
	 int flag;
	 int w;
	 int h;
	 int *alt;
	// int *fwd_inv;
} ptrs;

char *fff;
int main(int argc, char *argv[]) {
	
	FILE *inptr,*outptr;
	  char *ch;
	   int tmp,loop;
	 
	  int *red_s_ptr, *gr_s_ptr, *bl_s_ptr;
	  int *wptr,*wptr1,*wptr2;
	  int *alt,*alt1,*alt2, *inpbuf;
	
	 
	 char *buf1,buf2;
	  int n1 = 4096;
	 int n2 = 65536, size;
	  int ur,ug,ub,x,y,z;
	 int *fwd_inv;	

	 int i,j;
	
	 

	ptrs.w = ( int) atoi(argv[1]);
	ptrs.h = ( int) atoi(argv[2]);
	size = ptrs.w*ptrs.h*2;
	//ch = argv[3];
	printf("ptrs.w %d ptrs.h %d malloc of ptrs.inpbuf %d \n",ptrs.w,ptrs.h,size);
    printf("fname %s \n",argv[3]);
		//strncpy(fff, argv[3], sizeof(fff) - 1);
    //printf("address of fname 0x%x \n", &fff);
    
    //return 0;
    /*
     *Reads char data from argv[3] buf1 points to char data which is read in first half ptrs,inpbuf
    */ 
    buf1 = ( char *)malloc(ptrs.w*ptrs.h);
    buf2 = buf1;
	inpbuf = (  int *)malloc(ptrs.w*ptrs.h*2);
    
	printf("ptrs.inpbuf = 0x%x\n",inpbuf);
	//ptrs.inpbuf = buf;
	//printf("ptrs.buf = 0x%x\n",ptrs.inpbuf);
	
	 
	//loop = ptrs.w*ptrs.h;
    	//for(i=0;i<loop;i++)	
	printf("reading \n");
	ptrs.flag = tmp; 
	inptr = fopen(argv[3],"rb");
	printf("inptr %d \n",inptr);
	if(!inptr)
	{
		printf("Unable to open file!");
		return 1;
	}
	else 
	{
		printf("size %d sizeof(buf1) 0x%x\n",size,sizeof(buf1));
		n1 = fread(buf1,sizeof(*buf1),size/2,inptr);
        printf("number of char read %d\n",n1);

	}
	for(i=0;i<n1;i++)
	{
		printf("i %d 0x%x ",i,*buf1);
		buf1++;
	}
	buf1 = buf1 -n1;
	printf("\n");
	fwd_inv = ( int *)malloc(1);
	printf("fwd_inv = 0x%x\n",fwd_inv);
	tmp = ( int) atoi(argv[4]);
	if (tmp == 0) 
	{ 
			
		*fwd_inv = ( int) tmp;
		printf("fwd lifting then inv lifting step  %d *fwd_inv 0x%x \n",*fwd_inv,fwd_inv);
	}
	else if (tmp == 1) 
	{
			
		*fwd_inv = ( int) tmp;
		printf("fwd lifting step only 0x%x *fwd_inv %d \n",*fwd_inv,fwd_inv);
	}
	
	//n2= (ptrs.w*ptrs.h);
	//printf("number to be read %d \n", n2);
	//buf2 = ( char *)malloc(sizeof( n1 ));
	//printf("buf = 0x%x %d\n",buf,*buf1);
	//size = size-ptrs.w*ptrs.h;
	printf("starting transfer between buf1 and ptrs.inpbuf \n");
	for(i=0;i<ptrs.w*ptrs.h;i++)
	{
		ptrs.inpbuf[i] = *buf1;
		//printf("i %d 0x%x 0x%x\n",i,*buf1,*ptrs.inpbuf);
		//printf("i %d 0x%x 0x%x ",i,*buf1,*inpbuf);
		printf("i %d 0x%x 0x%x ",i,*buf1,ptrs.inpbuf[i]);
		buf1++;
		//inpbuf++;
    }
	printf("\n");
    //inpbuf = inpbuf - ptrs.w*ptrs.h;
    printf("&ptrs.inpbuf[0] = 0x%x\n",&ptrs.inpbuf[0] );
    
    //wptr = ( int)inpbuf;
    wptr = &ptrs.inpbuf[0];
    //wptr = buf1;
    //wptr = ptrs.inpbuf;
	printf("wptr = 0x%x\n",wptr);
	printf("ptrs.inpbuf = 0x%x\n",inpbuf); 
	//ptrs.alt = ptrs.w*ptrs.h*2;
	//ptrs.alt = inpbuf + ptrs.w*ptrs.h*2;
	ptrs.alt = &ptrs.inpbuf[ptrs.w*ptrs.h];
	printf("ptrs.alt = 0x%x\n",&ptrs.inpbuf[ptrs.w*ptrs.h]);
	printf("starting dwt\n");
    
	lifting(ptrs.w,wptr,ptrs.alt,fwd_inv);
	printf("finished dwt\n");
	//size = size-ptrs.w*ptrs.h;
	
	//for(i=0;i<4095;i++)
	for(i=0;i<4096;i++)
	{
		//*ptrs.inpbuf = *buf1;
		printf("i %d 0x%x \n",i,ptrs.inpbuf[i]);
		//buf1++;
		//inpbuf++;
    }
    //ptrs.inpbuf = ptrs.inpbuf - 4095;
    //inpbuf = inpbuf - ptrs.w*ptrs.h;
    
    //printf("i %d 0x%x %d\n",i,*ptrs.inpbuf,sizeof(ptrs.inpbuf));
		//pack(ptrs.flag, i,buf_red, ptrs.inpbuf);
	
    outptr = fopen("dwt.bin","wb");
	if (!outptr)
	{
		printf("Unle to open file!");
		return 1;
	}
	//else fwrite(wptr,sizeof( int),4096,outptr);
	else 
	{	
		//fwrite(ptrs.inpbuf, sizeof(ptrs.inpbuf),1,outptr);
		fwrite(wptr,sizeof( int),4096,outptr);
		//fwrite(alt,sizeof(  int),65536,outptr);
		fclose(outptr);
	}
	//free(buf1);
	//free(buf2);
	return 0;

}
