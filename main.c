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
#include "JimmyNeutron.h"
#include "Learning.h"

int main ( int argc, char *argv[] )
{

    NeuralNet* NN = NnGetXorToXorNn(0);
    NnBigPrint(NN);

    //lrnSaveNeuralNet(NN, "save.txt");

    //lrnLoadNeuralNet(NN2, "save.txt");
     

    
    
  /*
  Mat *m = learningNN("ascii2.bmp");
  int i = 0;
=======
>>>>>>> 85d998541630efdc1a0c3b51f205d5c1ee810f90
  
 
  Mat *m = learningNNOutput();
  int h = 0;
  for(int i = 0; i < 24; i++)
    {
      for (int j = 0; j < 24; j++)
	{
	  printf("%1.0f ",mGet(m,i,j));
	  h++;
	    if ( h == 24)
	      {
		h = 0;
		printf("\n");
	      }
       }      
       }*/
  
  
  
  // /afs/cri.epita.net/user/b/be/benete_p/u/projet/ThirdEye/Archives/asciitable.bmp
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

  /* Bitmap k = LoadToBitmap("wow.bmp");
      Bitmap * bmp = &k;
      List *l = CutAll(bmp);
      struct listB *res = sendList(l,bmp);

	while (!is_emptyB(res))
	{
		printBitmap(res->bmp);
		res = res->next;
	}*/
	
 
	return 1;
//	Init(argc, argv);
}

