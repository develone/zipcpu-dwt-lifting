
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "lifting.h"
#include "pnmio.h"

		struct PTRs {
			short int inpbuf[131072];
	 
			int flag;
			short int w;
			short int h;
			short int *alt;
			// int *fwd_inv;
		}ptrs;

char *fff;
int main(int argc, char *argv[]) {
	
	FILE *inptr,*outptr;
	  char *ch;
	   int tmp,loop;
	 unsigned char *img1;
	 int ncols, nrows;
	 
	  int *red_s_ptr, *gr_s_ptr, *bl_s_ptr;
	  short int *wptr,*wptr1,*wptr2;
	  short int *alt,*alt1,*alt2, *inpbuf;
	
	 
	 char *buf1,buf2;
	 int n1;
	 int  size;
	  int ur,ug,ub,x,y,z;
	 short int *fwd_inv;	
	 short int *decomp;

	 int i,j;
	
	 


	if (argc > 2) 
	{
		
		printf("argc %d \n",argc);

		
		ptrs.w = (int) atoi(argv[3]);
		ptrs.h = (int) atoi(argv[4]);
		//decomp = (short int)atoi(argv[5]);
		//printf("decomp  %d *fwd_inv 0x%x \n",*decomp,decomp);
		size = ptrs.w*ptrs.h*2;
		
		img1 = pgmReadFile(argv[1], NULL, &ncols, &nrows);
		printf("ptrs.w %d ptrs.h %d malloc of ptrs.inpbuf %d \n",ptrs.w,ptrs.h,size);
		printf("fname %s \n",argv[1]);	
		
		/*
		*Reads char data from argv[1] buf1 points to char data which is read in first half ptrs,inpbuf
		*/ 
		buf1 = ( char *)malloc(ptrs.w*ptrs.h);
		buf2 = buf1;
		inpbuf = (  int *)malloc(ptrs.w*ptrs.h*2);
    
		printf("ptrs.inpbuf = 0x%x\n",inpbuf);
	
		printf("reading \n");
		ptrs.flag = tmp;
		fwd_inv = ( short int *)malloc(1);
		//*decomp = ( short int *)malloc(1);
		printf("fwd_inv = 0x%x\n",fwd_inv);
		tmp = ( int) atoi(argv[2]);
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
	}else 
	{
		printf("argc %d \n",argc);
		ptrs.w = (int) atoi(argv[3]);
		ptrs.h = (int) atoi(argv[4]);
		//*decomp = (short int)atoi(argv[5]);
		//printf("decomp  %d *fwd_inv 0x%x \n",*decomp,decomp);
		size = ptrs.w*ptrs.h*2;
		img1 = pgmReadFile(argv[1], NULL, &ncols, &nrows);
		printf("ptrs.w %d ptrs.h %d malloc of ptrs.inpbuf %d \n",ptrs.w,ptrs.h,size);
		printf("fname %s \n",argv[1]);
	
	
	


		/*
		*Reads char data from argv[1] buf1 points to char data which is read in first half ptrs,inpbuf
		*/ 
		buf1 = ( char *)malloc(ptrs.w*ptrs.h);
		buf2 = buf1;
		inpbuf = (  int *)malloc(ptrs.w*ptrs.h*2);
    
		printf("ptrs.inpbuf = 0x%x\n",inpbuf);
	
		printf("reading \n");
		ptrs.flag = tmp;
		fwd_inv = ( int *)malloc(1);
		decomp = ( short int *)malloc(1);
		printf("fwd_inv = 0x%x\n",fwd_inv);
		tmp = ( int) atoi(argv[2]);
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
	}
	
	printf("starting transfer between buf1 and ptrs.inpbuf \n");
	for(i=0;i<ptrs.w*ptrs.h;i++)
	{
		ptrs.inpbuf[i] = *img1;
		
		printf("i %d 0x%x 0x%x ",i,*buf1,ptrs.inpbuf[i]);
		img1++;
		
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
	
	
	
	for(i=0;i<ptrs.w*ptrs.h;i++)
	{
		
		printf("i %d 0x%4hx \n",i,ptrs.inpbuf[i]);
		
    }

	
    outptr = fopen("dwt.bin","wb");
	if (!outptr)
	{
		printf("Unle to open file!");
		return 1;
	}
	
	else 
	{	
		
		fwrite(wptr,sizeof(short int),ptrs.w*ptrs.h,outptr);
		
		fclose(outptr);
	}
	//free(buf1);
	//free(buf2);
	return 0;

}
