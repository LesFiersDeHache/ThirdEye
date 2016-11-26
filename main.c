#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <assert.h>
#include "NeuralNet.h"
#include "Sigmoid.h"
#include <time.h>
#include "list.h"
#include "CutBitmap.h"
#include "SDLstuff.h"
#include "Bitmap.h"
#include "Matrix.h"
#include "resize.h"
#include "save.h"
#include "Graphics.h"
#include "listB.h"

Mat* learningNNOutput();
Mat* learningNN();

int main ( int argc, char *argv[] )
{

	/*Mat* W0 = mNewFill(10,10,-50.45698099);
	Mat* W1 = mNewRand(15,15,2,-1);
	Mat* B0 = mNewRand(5,5,3,5);
	Mat* B1 = mNewRand(10,10,3,-2);
	
	NnSave(W0,W1,B0,B1,"save.txt");

	W0 = mNewFill(10,10,0);
        W1 = mNewFill(15,15,0);
        B0 = mNewFill(5,5,0);
        B1 = mNewFill(10,10,0);

	NnLoad(W0,W1,B0,B1,"save.txt");
	
	mPrintExt(W0, "W0 MAT");
        mPrintExt(W1, "W1 MAT");
        mPrintExt(B0, "B0 MAT");
        mPrintExt(B1, "B1 MAT");
	*/

      Bitmap k = LoadToBitmap("wow.bmp");
      Bitmap * bmp = &k;
      List *l = CutAll(bmp);
      struct listB *res = sendList(l,bmp);

	/*while (!is_emptyB(res))
	{
		printBitmap(res->bmp);
		res = res->next;
	}*/
	
	printf("PIX : %d", getPixel(res->bmp,3,4));
	return 1;
//	Init(argc, argv);
}

Mat* learningNNOutput()  // Create the Matrix Output for the learning
{
  Mat *m2 = mNewFill(5,10,0);  
  int j = 0;
  for (int i = 0; i < 5; i++)  
    {      
      mSet(m2,i,j,1);
      j++;     
    }
  return m2;
}

Mat* learningNN(char *path) // Create the Matrix associated to the image.
{                           // It's the Path of the image
  // /afs/cri.epita.net/user/b/be/benete_p/u/projet/ThirdEye/Archives/asciitable.bmp
  Bitmap k = LoadToBitmap(path); 
  Bitmap * bmp = &k;
  List *l = CutAll(bmp);
  struct listB *res = sendList(l,bmp);     
  Mat *m = mNewFill(94,24*24,0);
  Bitmap *b = res->bmp;	 
  for (int i = 0; i < 94; i++)
    {             
      for (int j = 0; j < 24*24; j++)
	{	 
	  b = res->bmp;		       
	  if (b->p_bitmap[j] == 1)
	    {	      
	      mSet(m,i,j,1);
	    }	  
	}
      res = res->next;
    }
  return m;
  }
