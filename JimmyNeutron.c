#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <err.h>

#include "NeuralNet.h"
#include "Matrix.h"
#include "save.h"
#include "Bitmap.h"
#include "list.h"
#include "CutBitmap.h"
#include "SDLstuff.h"
#include "listB.h"
#include "resize.h"

// ############ INIT ##################//

static Mat* learningNNOutput()  // Create the Matrix Output for the learning
{
  Mat *m2 = mNewFill(94,94,0);  
  int j = 0;
  for (int i = 0; i < 94; i++)  
    {      
      mSet(m2,i,j,1);
      j++;     
    }
  return m2;
}

Mat* learningNN(char *path) // Create the Matrix associated to the image.
{                           // It's the Path of the image
  Bitmap k = LoadToBitmap(path); 
  Bitmap * bmp = &k;
  List *l = CutAll(bmp);
  struct listB *res = sendList(l,bmp);  
  struct listB *print = res;
  while (!is_emptyB(print)) {
      printBitmap(print->bmp);
      print = print->next;
  }
  Mat *m = mNewFill(94,24*24,0);
  Bitmap *b = res->bmp;  
  for (int i = 0; i < 94; i++)
    {
      //printBitmap(res->bmp);
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

static void initLearningMatrix(Mat* Input, Mat* Output) {

    Mat* _In = learningNN("ascii5.jpg");
    Mat* _Out = learningNNOutput();

    mPrintDim(_Out, "Out");
    mPrintDim(Output, "Output");
    mCopyAinB(_In, Input);
    mCopyAinB(_Out, Output); // NOT SAME DIM !!!

    mFree(_In);
    mFree(_Out);
}

NeuralNet* JnInitJn() {

    Mat* Input = mNewFill(94, 24*24, 0.0);
    Mat* Output = mNewFill(94, 94, 0.0);

    initLearningMatrix(Input, Output);

    NeuralNet* JN = NnInit(Input, Output, 30, 94);

    mFree(Input);
    mFree(Output);

    return JN;
}

// ############ SAVE/LOAD #############//

void JnLoadWeights(NeuralNet* JN) {

    NnLoad(JN->w0to1, JN->w1to2, JN->b1, JN->b2, "Jimmy.txt");
}

void JnSaveWeights(NeuralNet* JN) {

    NnSave(JN->w0to1, JN->w1to2, JN->b1, JN->b2, "Jimmy.txt");
}

// ############ LEARNING ##############//

void JnLearnOneTime(NeuralNet* JN) {

    NnLearn(JN);
}

void JnLearn(NeuralNet* JN, size_t loop) {

    
    for (size_t l = 0 ; l < loop ; ++l ) {

        JnLearnOneTime(JN);

        if (l % 100 == 0) {

            warnx("Round : %ld -> Error : %f", l, NnGetError(JN));
        }
    }

    warnx("#### OVER ####");
}

// ######### CALC ERROR ############ //


