#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <assert.h>
#include "NeuralNetwork.h"
#include "FeedForward.h"
#include "BackFeed.h"
#include "Sigmoid.h"
#include <time.h>
#include "list.h"
#include "CutBitmap.h"
#include "SDLstuff.h"
#include "Bitmap.h"
#include "Matrix.h"


#define NB_OF_LOOPS 5
#define MODE 1
#define PRINT 1
void neuralLearning(NeuralNetwork* NN, Outputs* outputs,
                    unsigned int nb_of_feeding);
 
float neuralTesting(NeuralNetwork* NN, Outputs* outputs,
                   unsigned int nb_of_testing);





void matrixTests();

void NNTexts()
{
// ##### INIT ##### //
 
  // SET RANDOM
  printf("###### LET'S BEGIN THIS! #####\n\n");
  srand(time(NULL));
 
  // INIT NEURAL NETWORK
  NeuralNetwork NN_struct;
  NeuralNetwork* NN = &NN_struct;
 
  unsigned int nb_neurons[3] = {2, 3, 1};
 
  initNeuralNetwork(NN, 3, nb_neurons);
  printf("#### NEURAL NETWORK ####\n\n");
  printNeuralNetwork(NN);
 
  // INIT OUTPUTS
 
  Outputs outputs_struct;
  Outputs* outputs = &outputs_struct;
 
  // ##### EXEC ##### //
 
  float p = 0;
  float q = 0;
 
  switch (MODE) {
    case 0 :
      neuralLearning(NN, outputs, NB_OF_LOOPS);
      break;
 
    case 1 :
      p = neuralTesting(NN, outputs, NB_OF_LOOPS);
      neuralLearning(NN, outputs, NB_OF_LOOPS);
      q = neuralTesting(NN, outputs, NB_OF_LOOPS);
      printf("%f ; %f", p, q);
      break;
 
    default :
      err(1, "bad argument");
      break;
    }
}

int main(int argc, char *argv[])
{
 
  printf("ARGC%s\n",argv[1]);
  int Sel = 0;
  if(argc!=0)
    Sel = atoi(argv[1]);
  if(Sel<5)
    {
      Bitmap k ;
      if(Sel==1)
    {
      k = LoadToBitmap("Color.bmp");
      Bitmap * bmp = &k;
      display_image(BitmapToSurface(bmp));
    }
      else if(Sel==2)
        k = LoadToBitmap("wow.bmp");
      else if(Sel==3)
        k = LoadToBitmap("wow2.bmp");
      else
        k = LoadToBitmap("wow5.bmp");
      if(Sel !=1)
    {
      Bitmap * bmp = &k;
      CutAll(bmp);
    }
    }
  else if(Sel==5)
    {
	matrixTests();     
    }
  else
    {
      NNTexts();
    }
 
 
}


void matrixTests() {
    
    printf("####################\n");
    printf("#   MATRIX TESTS   #\n");
    printf("####################\n");
    printf("\n");
    printf("INITS\n");
    printf("Matrix 6x4 filled with 0.0\n");
    Mat* mat0 = newMat(6, 4, 0.0);
    printMat(mat0);
    printf("Matrix 3x2 filled randomly\n");
    Mat* mat1 = newMatRandom(3, 2, 2, -1);
    printMat(mat1);
    printf("\nGETS/SETS\n");
    printf("Get components of this matrix :\n");
    printMat(mat1);
    printf("(0, 1) = %f\n", getInMat(mat1, 0, 1));
    printf("(1, 0) = %f\n", getInMat(mat1, 1, 0));
    printf("Set compenent of this matrix : (0, 2) = 1.0\n");
    setInMat(mat1, 1, 1, 1.0);
    printMat(mat1);
    printf("MATHS OPERATIONS\n");
    printf("With theses matrix :\n");
    Mat* m = newMat(3, 2, 1.0);
    Mat* m2 = newMat(3, 2, 2.0);
    printMat(m);
    printf("Matrix + 2 = \n");
    printMat(ope_MpR(m, 2));
    printf("Matrix * 2 = \n");
    printMat(ope_MxR(m, 2));
    printf("Matrix + Matrix = \n");
    printMat(ope_MpM(m, m2));
    printf("Matrix * Matrix (classic multiplication 1 by 1) = \n");
    printMat(ope_MxM(m, m2));
    printf("Matrix transpose = \n");
    printMat(ope_Mt(m));
    printf("Apply sigmoid to matrix\n");
    printMat(ope_apply_sigmoid(m));
    printf("Apply sigmoid deriv to matrix\n");
    printMat(ope_apply_deriv_sigmoid(m));

}

void neuralLearning(NeuralNetwork* NN, Outputs* outputs,
                    unsigned int nb_of_feeding)
{
 
  printf("\n\n#######################\n");
  printf("### Engage learning ###\n");
  printf("#######################\n\n");
 
  for (unsigned int i = 0 ; i < nb_of_feeding ; ++i)
  {
    #if PRINT != 0  
    printf("## ENGAGE LEARNING N°%d! ##\n", i);
    #endif
 
    short a = rand() % 2;
    short b = rand() % 2;
    short expected_output = (a != b);
   
    #if PRINT != 0
    printf("## Testing with : ");
    printf("a = %d ; b = %d ; exp_out = %d ##\n", a, b, expected_output);
    #endif
 
    float inputs[2] = {(float)a, (float)b};
   
    #if PRINT != 0
    printf("\n## FEEDING n.%d in progress... ##\n", i);
    #endif
    // FeedForward
    feedForward(NN, inputs, 2, outputs);
   
    #if PRINT != 0  
    printf("# Feeding n.%d over #\n", i);
    printf("# New Outputs : #\n");
    printOutputs(outputs, 0);
    printf("\n## UPDATING n.%d of the neural network... ##\n", i);
    #endif
 
    // Update Weight
    UpdateWeight(NN, expected_output, outputs,1.0);
   
    #if PRINT != 0
    printf("# Updating n.%d over. #\n", i);
    printf("# New Weights : \n");
    printNeuralNetwork(NN);
    printf("## END OF LEARNING N°%d! ##", i);
    #endif
  }
  warnx("\n### Learning complete. ####");
  printNeuralNetwork(NN);
  printOutputs(outputs, 0);
}
 
float neuralTesting(NeuralNetwork* NN, Outputs* outputs,
                   unsigned int nb_of_testing)
{
  unsigned int nb_of_win = 0;
  float final_output;
  short bool_output;
 
  for (unsigned int i = 0 ; i < nb_of_testing ; ++i)
  {
    short a = rand() % 2;
    short b = rand() % 2;
    #if PRINT != 0
    warnx("a = %d ; b = %d\n", a, b);
    #endif
   
    short expected_output = (a != b);
 
    float inputs[2] = {(float)a, (float)b};
 
    feedForward(NN, inputs, 2, outputs);
 
    final_output = getOutput(outputs, 3, 0);
    bool_output = (final_output > 0.5);
 
    if (bool_output == expected_output)
    {
      nb_of_win++;
    }
  }
 
  warnx("Percentage of win = %f", (float)nb_of_win / (float)nb_of_testing);
  return (float)nb_of_win / (float)nb_of_testing;
}

