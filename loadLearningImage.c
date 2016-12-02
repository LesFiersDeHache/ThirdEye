#include "NeuralNet.h"
#include "Matrix.h"
#include "save.h"
#include "Bitmap.h"
#include "list.h"
#include "CutBitmap.h"
#include "SDLstuff.h"
#include "listB.h"
#include "resize.h"
#include "loadLearningImage.h"

// ############ INIT ##################//

Mat* learningNNOutput()  // Create the Matrix Output for the learning
{
  Mat *m2 = mNewFill(94,94,0);  
  int j = 2;
  mSet(m2,0,1,1);
  mSet(m2,1,0,1);
  for (int i = 2; i < 94; i++)  
    {      
      mSet(m2,i,j,1);
      j++;     
    }
  return m2;
}

Mat* learningNN(char *path) // Create the Matrix associated to the image.
{                           // It's the Path of the image (ascii6.bmp)
  Bitmap k = LoadToBitmap(path); 
  Bitmap * bmp = &k;
  List *l = CutAll(bmp);
  struct listB *res = sendList(l,bmp);  
  struct listB *print = res;
  while (!is_emptyB(print)) {
      //printBitmap(print->bmp);
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


		      
Mat* listbmpToMat(struct listB *res) // Create the Matrix associated to the image.
{   
  int len = 0;
  struct listB *print = res;
  while (!is_emptyB(print))
  {
      //printBitmap(print->bmp);
    print = print->next;
    len++;	   
  }
  Mat *m = mNewFill(len,24*24,0);
  Bitmap *b = res->bmp;  
  for (int i = 0; i < len; i++)
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
	      
