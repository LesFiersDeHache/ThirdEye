#include <stdlib.h>
#include <stdio.h>
#include "Bitmap.h"
#include "list.h"
#include  "CutBitmap.h"
struct list* cutblockY(Bitmap bmp)
{
	printf("incutblocky\n" );
	int Threshold = 0;
	int policeSize = 0;
	int white = 0;
	unsigned short Ymin = 0;
	unsigned short ymax;
	int isStillBlack = 0;
	int firstblack = 1;
	struct list* result;

	for(unsigned short y = 0;y<bmp.height;y++)
	{
		//printf("\n" );
		for(unsigned short x= 0; x<bmp.width;x++)
		{

			unsigned short k= getPixel(&bmp,x,y);
				//printf("%d",k );
			//printf("%d\n",k );
			if(k==0)
				isStillBlack = 1;
		}
		if(isStillBlack)
		{
			policeSize+= 1;
			if(firstblack)
			{
				firstblack = 0;
				Ymin = y;
			}
		}
		else
		{
	
			if(policeSize > 3 && Threshold == 0)
				Threshold =4*policeSize;
			if(Threshold!=0)
			{
				white += 1;
				if(white>Threshold || y+1 == bmp.height)
				{
					ymax = y;
					Bitmap b;
					adjustBitmap(&bmp,&b,0,Ymin,bmp.width,ymax);
					printf("%d\n",Ymin );
					printf("%d\n", ymax);
					list_push_front(result,b);
					firstblack = 1;
					Ymin = 0;
					ymax = 0;
					isStillBlack = 0;
					white = 0;
					policeSize = 0;
					Threshold = 0;
				}
			}
		}
	
		isStillBlack = 0;

	}
	return result;
};

struct  list* cutBlockX(Bitmap bmp,int policeSize)
{
	int Threshold = 4*policeSize;
	int white = 0;
	unsigned short Xmin = 0;
	unsigned short Xmax = 0;
	unsigned short isStillBlack = 0;
	unsigned short firstblack = 1;
	struct list* result;

	for (int x= 0; x<bmp.width;x++)
	{
		//printf("%d\n",Threshold );
		for(int y = 0; y<bmp.height;y++)
		{
			unsigned short k = getPixel(&bmp,x,y);
			if(k==0)
				isStillBlack = 1;
		}
		if(isStillBlack)
		{
			if (firstblack)
			{
				firstblack = 0;
				Xmin =x;
			}
			isStillBlack = 0;
		}
		else
		{
			if(firstblack==0)
			{
				white+= 1;
				if(white > Threshold)
				{
					Xmax =x ;
					Bitmap b;
					adjustBitmap(&bmp,&b,Xmin,0,Xmax,bmp.height);
					printf("%d\n", Xmin);
					printf("%d\n",Xmax );
					list_push_front(result,b);
					firstblack =1;
					Xmin = 0;
					Xmax = 0;
					white = 0;
					Threshold = 0;
				}
				isStillBlack = 0;
			}
		}
	}
	return result;
};

struct list* CutLines(Bitmap bmp)
{
	 unsigned short Ymin = 0;
	 unsigned short ymax = 0;
	 int x = 0;
	 unsigned short isStillBlack = 0;
	 unsigned short firstblack = 1;
	 unsigned short isblack = 0;
	 unsigned short initblock = 0;

	 struct list* result;
	 int height = bmp.height -1;

	 for(int y= 0; y<bmp.height;y++)
	 {
	 	while(x<bmp.width&&!isblack)
	 	{
	 		unsigned short k = getPixel(&bmp,x,y);
	 		if(k==0)
	 		{
	 			//printf("black\n");
	 			isblack = 1;
	 			isStillBlack =1;
	 		}
	 		x+=1;
	 	}
	 	x= 0;
	 	if(isStillBlack&& y!= height)
	 	{
	 		if(firstblack)
	 		{
	 			firstblack = 0;
	 			initblock = 1;
	 			Ymin = y;
	 		}
	 	}
	 	else
	 	{
	 		if(initblock)
	 		{
	 			printf("%d\n",Ymin);
	 			printf("%d\n",y );
	 			ymax = y;
	 			Bitmap b ;
	 			printf("bitmapheight%d\n", b.width);
	 			adjustBitmap(&bmp,&b,0,Ymin,bmp.width,ymax);
	 			printf("afteradj\n");
	 			list_push_front(result,b);
	 			Ymin = 0;
	 			ymax = 0;
	 			isblack = 0;
	 			isStillBlack = 0;
	 			firstblack = 1;
	 			initblock = 0;
	 		}
	 	}
	 	isStillBlack = 0;
	 	isblack = 0;
	 }
	 return result;
};