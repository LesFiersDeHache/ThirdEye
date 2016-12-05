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
#include "loadLearningImage.h"

int main ( int argc, char *argv[] )
{

    THE_TEST_NN_01();
    THE_TEST_NN_02();
    THE_TEST_NN_03();
    //lrnStartLearning("ascii6.bmp", "save.txt", 10000);

    /*
    NeuralNet* NN = NnGetXorToXorNn(50000);
    Mat* M = mNewFill(20, 20, 0.0);
    matToDiag(M);
    mPrintCompact(M, "M");
    mMirrorInPlace(M);
    mPrintCompact(M, "M");
    Mat* M2 = mT(M);
    NN->l0 = M2;
    NnFeedForward(NN);
    NnBigPrint(NN);
    */
    //NnBigPrint(NN);


    //lrnInitNeuralNet("ascii6.bmp", "save.txt");

    //Mat* M = learningNN("ascii6.bmp");

    //char* s = getCharFromMat(M);
    //printf("THING %s", s);
    //lrnStartLearning("ascii6.bmp", "save.txt", 1000000);
//<<<<<<< HEAD
    //Init(argc,argv);
//=======
    //Init(argc,argv);
//>>>>>>> 7d148e7c37c7f8c0e360cc743e16291e56f66c27

/*
    //lrnSaveNeuralNet(NN, "save.txt");
    //lrnInitNeuralNet("ascii6.bmp", "save.txt");
    //lrnStartLearning("ascii6.bmp", "save.txt", 100000);
    //NeuralNet* NN = NnGetXorToXorNn(50000);
    //NnBigPrint(NN);
    Init(argc,argv);
    lrnInitNeuralNet("ascii6.bmp", "save.txt");
>>>>>>> a600222d10264eaeaae97bcf2e130a9091528ab6

    //lrnLoadNeuralNet(NN2, "save.txt");
     
*/
    
    
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
  
  //Init(argc,argv);
  
  // /afs/cri.epita.net/user/b/be/benete_p/u/projet/ThirdEye/Archives/asciitable.bmp
	/*Mat* W0 = mNewFill(5,1,6.91919191562165);
	Mat* W1 = mNewRand(1,5,2,-1);
	Mat* B0 = mNewRand(5,1,3,5);
	Mat* B1 = mNewRand(5,1,3,-2);
	
	NnSave(W0,W1,B0,B1,"save.txt");

	W0 = mNewFill(5,1,0);
        W1 = mNewFill(5,1,0);
        B0 = mNewFill(5,1,0);
        B1 = mNewFill(5,1,0);

	NnLoad(W0,W1,B0,B1,"save.txt");
	
	//mPrintExt(W0, "W0 MAT");
       // mPrintExt(W1, "W1 MAT");
        //mPrintExt(B0, "B0 MAT");
        //mPrintExt(B1, "B1 MAT");
	*/

      /*Bitmap k = LoadToBitmap("Test8x8.bmp");
      Bitmap * bmp = &k;
      showResize(bmp);*/
      //DoAll(bmp);
      //List *l = CutAll(bmp);
      //struct listB *res = sendList(l,bmp);

	/*while (!is_emptyB(res))
	{
		printBitmap(res->bmp);
		res = res->next;
	}*/
	
 
	return 1;
//	Init(argc, argv);
}

