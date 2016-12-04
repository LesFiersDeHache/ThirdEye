#include <stdlib.h>
#include <stdio.h>
#include "Bitmap.h"
#include "list.h"
#include "CutBitmap.h"
#include "err.h"
#include "SDLstuff.h"
#include "SDL/SDL_image.h"
#include "listB.h"


static int Max(int a, int b)
{
  if (a > b) {return a;}
  else {return b;}
}

static int GoodSize(int a, int b)
{

/*Set the good size of the new Bitmap*/
  int res = Max(a,b);
  if (res % 2)
    {
      return res + 1;
    }
  else
    {
      return res;
    }
}

Bitmap* AdjustChar(List l, Bitmap *b)
{
  //l = cutHeight(l,b);
  int xMin = l.a;
  int xMax = l.b;
  int yMin = l.c;
  int yMax = l.d;	
  

  //printf("xMin : %d    xMax :  %d    yMin :  %d    yMax :  %d\n\n", xMin, xMax, yMin, yMax);
  int width = xMax - xMin;
  int height = yMax - yMin + 1;

  int size = GoodSize(width, height);
  /*if (height + 1 == size && height > width)
  {
	++height;
  }
  else if (width + 1 == size && width > height)
  {
	++width;
  }*/

  Bitmap* result;
  result = malloc(sizeof(Bitmap));
  
  bitmapInit(result,size,size);

  int count_width = (size - width) / 2;
  //printf("WIDTH SHIFT : %d\n", count_width);
  int count_height = (size - height) / 2;
  //printf("HEIGHT SHIFT : %d\n", count_height); 


  for (int i = 0; i < width; ++i)
    {
      for (int j = 0; j < height; ++j)
	{
	  setPixel(result,i + count_width,j + count_height, getPixel(b,i + xMin,j + yMin));
	}
     }

    
  printBitmap(result);  
  return result;
}



Bitmap* sizeUP(Bitmap* b)
{
	int size = 24;
	if (b->height != b->width)
	{
		warnx("NOT THE SAME SIZE !");
	}
	float size_mod = size / (float)(b->height);
	Bitmap *result;
	result = malloc(sizeof(Bitmap));
	bitmapInit(result,size,size);
	for (int x = 0; x < size; ++x)
	{
		for (int y = 0; y < size; ++y)
		{
			setPixel(result,x,y,getPixel(b,x / size_mod, y / size_mod));
		}
	}
        printf("\nIMAGE RESIZED UP : MOD = %f\n\n", size_mod);
	printBitmap(result);
	freeBitmap(b);
	return result;
}


Bitmap* sizeDO(Bitmap *b)
{

	int size = 24;
	if (b->height != b->width)
	{
		warnx("NOT THE SAME SIZE");
	}
	float size_mod = size / (float)(b->height);
	Bitmap* result;
	result = malloc(sizeof(Bitmap));
	bitmapInit(result,size,size);
	for (int x = 0; x < size; ++x)
	{
		for (int y = 0; y <size; ++y)
		{
			setPixel(result,x,y,getPixel(b,x / size_mod, y / size_mod));
		}
	}
	printf("\nIMAGE RESIZED DOWN : MOD = %f\n\n", size_mod);
	printBitmap(result);
	freeBitmap(b);
	return result;
}


Bitmap* fromCutToNN( List l, Bitmap* b)
{
	printf("\nADJUSTED CHAR BEFORE RESIZING :\n");
	Bitmap* result = AdjustChar(l, b);
	if (result->height != 24)
	{
		if (result->height < 24)
		{
			result = sizeUP(result);
		}
		else
		{
			result = sizeDO(result);
		}
	}
	return result;
}


void lettersPrettyPrint(List *l, Bitmap* b)
{
	int i = 0;
	printf("START DISPLAY\n\n");
	while (!is_empty(l))
	{
		fromCutToNN(*l,b);
		l = l->next;
		++i;
	}
	printf("END OF DISPLAY : NUMBER OF CHAR : %d\n",i);
}


struct listB* sendList(List *l, Bitmap* b)
{
	struct listB* res = empty_listB();
	res = push_frontB(fromCutToNN(*l,b),res);
	l = l->next;
	while (!is_empty(l))
	{
		Bitmap *bmp = fromCutToNN(*l,b);
		res = push_frontB(bmp, res);
		l = l->next;
	}
	freeList(l);
	/*while (!is_emptyB(res))
	{
		printf("IN BMP\n");
		printBitmap(res->bmp);
		res = res->next;
	}*/
	return res;
}

void showResize(Bitmap* b)
{
	List* l = CutAll(b);
	lettersPrettyPrint(l,b);
}
