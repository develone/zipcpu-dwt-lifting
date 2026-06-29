
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "lifting.h"

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
	
	printf("ptrs.w %d ptrs.h %d malloc of ptrs.inpbuf %d \n",ptrs.w,ptrs.h,size);
    printf("fname %s \n",argv[3]);

    /*
     *Reads char data from argv[3] buf1 points to char data which is read in first half ptrs,inpbuf
    */ 
    buf1 = ( char *)malloc(ptrs.w*ptrs.h);
    buf2 = buf1;
	inpbuf = (  int *)malloc(ptrs.w*ptrs.h*2);
    
	printf("ptrs.inpbuf = 0x%x\n",inpbuf);
	
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
        fclose(inptr);

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
	
	
	printf("starting transfer between buf1 and ptrs.inpbuf \n");
	for(i=0;i<ptrs.w*ptrs.h;i++)
	{
		ptrs.inpbuf[i] = *buf1;
		
		printf("i %d 0x%x 0x%x ",i,*buf1,ptrs.inpbuf[i]);
		buf1++;
		
    }
	printf("\n");
    
    printf("&ptrs.inpbuf[0] = 0x%x\n",&ptrs.inpbuf[0] );
    
    
    wptr = &ptrs.inpbuf[0];
    
	printf("wptr = 0x%x\n",wptr);
	printf("ptrs.inpbuf = 0x%x\n",inpbuf); 
	
	ptrs.alt = &ptrs.inpbuf[ptrs.w*ptrs.h];
	printf("ptrs.alt = 0x%x\n",&ptrs.inpbuf[ptrs.w*ptrs.h]);
	printf("starting dwt\n");
    
	lifting(ptrs.w,wptr,ptrs.alt,fwd_inv);
	printf("finished dwt\n");
	
	
	
	for(i=0;i<4096;i++)
	{
		
		printf("i %d 0x%x \n",i,ptrs.inpbuf[i]);
		
    }

	
    outptr = fopen("dwt.bin","wb");
	if (!outptr)
	{
		printf("Unle to open file!");
		return 1;
	}
	
	else 
	{	
		
		fwrite(wptr,sizeof( int),4096,outptr);
		
		fclose(outptr);
	}
	//free(buf1);
	//free(buf2);
	return 0;

}
