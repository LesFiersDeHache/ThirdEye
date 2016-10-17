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