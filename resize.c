#include <stdlib.h>
#include <stdio.h>
#include "Bitmap.h"
#include "list.h"
#include "CutBitmap.h"
#include "err.h"
#include "SDLstuff.h"
#include "SDL/SDL_image.h"

static int Max(int a, int b)
{
  if (a > b) {return a;}
  else {return b;}
}

static int GoodSize(int a, int b)
{
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


Bitmap AdjustChar(List l, Bitmap *b)
{
  int xMin = l.a;
  printf("%d\n",xMin);
  int xMax = l.b;
  int yMin = l.c;
  int yMax = l.d;

  int width = xMax - xMin + 1;
  int height = yMax - yMin + 1;

  int size = GoodSize(width, height);

  printf("%d\n",size);

  Bitmap result;
  
  bitmapInit(&result,size,size);

  int count = (size - Max(width,height)) / 2;

  warnx("%d",count);
  
  
  for (int i = 0; i < width; ++i)
    {
      for (int j = 0; j < height + 1; ++j)
	{
	  warnx("%d",getPixel(b, j + yMin, i + xMin));
	  setPixel(&result,count + i,count +  j, getPixel(b,i + xMin,j + yMin));
	}
     }

    
  printBitmap(&result);  
  return result;
}
