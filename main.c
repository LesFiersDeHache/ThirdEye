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
	return 1;

      /*Bitmap k = LoadToBitmap("wow.bmp");
      Bitmap * bmp = &k;
      List *l = CutAll(bmp);
      lettersPrettyPrint(l, bmp);
*/

//	Init(argc, argv);
}
