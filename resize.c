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


static List cutHeight(List l, Bitmap *b)     //USELESS IF LUCAS DOES WELL
{
  int xMin = l.a;
  int xMax = l.b;
  int yMin = l.c;
  int yMax = l.d;
  int condition = 0;
  int y = yMax;
  int x = xMax;
   

   printf("PIXEL %d\n",getPixel(b,xMin + 3,yMin + 4));
 
  while (!condition && y >= yMin) 
  {
	while (!condition && x >= xMin)
	{
		//printf("PIXEL %d\n",getPixel(b,x,y));
		if (getPixel(b,x,y) == 0)
		{
			condition = 1;
			warnx("BLACK\n");
		}
		--x;
	}
	if (!condition)
	{
		--yMax;
		warnx("YMAX %d \n",yMax);
	}
	--y;
	x = xMax;
  }
  l.d = yMax;
  return l;
}

Bitmap* AdjustChar(List l, Bitmap *b)
{
  //l = cutHeight(l,b);
  
  int xMin = l.a;
  int xMax = l.b;
  int yMin = l.c;
  int yMax = l.d;
  warnx("%d\n",yMax);

  int width = xMax - xMin + 1;
  int height = yMax - yMin + 1;

  int size = GoodSize(width, height);

  Bitmap* result;
  result = malloc(sizeof(Bitmap));
  
  bitmapInit(result,size,size);

  printBitmap(result);

  int count_width = (size - width) / 2;
  int count_height = (size - height) / 2;

  printf("COUNT%d\n",count_width);

  
  for (int i = 0; i < width; ++i)
    {
      for (int j = 0; j < height + 1; ++j)
	{
	  //warnx("YAAAAAAAAAAAA\n");
	  setPixel(result,i + count_width,j + count_height, getPixel(b,i + xMin,j + yMin));
	}
     }

    
  printBitmap(result);  
  return result;
}



Bitmap* sizeUP(Bitmap* b)
{
	if (b->height != b->height)
	{
		warnx("NOT THE SAME SIZE !");
	}
	float size_mod = 24 / (float)(b->height);  // MODIFY SIZE HERE
	warnx("MOD %f",size_mod);
	Bitmap *result;
	result = malloc(sizeof(Bitmap));
	bitmapInit(result,24,24);         //MODIFY SIZE HERE
	for (int x = 0; x < 24; ++x)
	{
		for (int y = 0; y < 24; ++y)
		{
			setPixel(result,x,y,getPixel(b,x / size_mod, y / size_mod));
		}
	}
	printBitmap(result);
	freeBitmap(b);
	return result;	
}
