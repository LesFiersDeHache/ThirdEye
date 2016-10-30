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

#define NB_OF_LOOPS 10000 
#define MODE 1
#define PRINT 0
void neuralLearning(NeuralNetwork* NN, Outputs* outputs, 
                    unsigned int nb_of_feeding);

float neuralTesting(NeuralNetwork* NN, Outputs* outputs, 
                   unsigned int nb_of_testing);

int main (int argc, char *argv[])
{
  Bitmap* b = LoadToBitmap("wow2.bmp");
  int tab[4] = {0,b->width,0,b->height};
  int PoliceSize = 19;
  List * L  = cutblockY(tab,b,&PoliceSize);
  print_list(L);
  
  // ##### INIT ##### //
  /*
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
  */
  return 0;
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
