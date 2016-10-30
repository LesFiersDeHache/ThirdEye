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

#define NB_OF_LOOPS 1
#define MODE 1

void neuralLearning(NeuralNetwork* NN, Outputs* outputs, unsigned int nb_of_feeding);

void neuralTesting(NeuralNetwork* NN, Outputs* outputs, unsigned int nb_of_testing);

int main (int argc, char *argv[])
{
  // ##### INIT ##### //

  // SET RANDOM
  warnx("1");
  srand(time(NULL));
  
  // INIT NEURAL NETWORK
  NeuralNetwork NN_struct;
  NeuralNetwork* NN = &NN_struct;

  unsigned int nb_neurons[3] = {2, 3, 1}; 
  
  initNeuralNetwork(NN, 3, nb_neurons);
  warnx("2");
  printNeuralNetwork(NN);
  warnx("3");
  
  // INIT OUTPUTS

  Outputs outputs_struct;
  Outputs* outputs = &outputs_struct;
  
  // ##### EXEC ##### //
  
  switch (MODE) {
    case 0 :
      neuralLearning(NN, outputs, NB_OF_LOOPS);
      break;
  
    case 1 :
      neuralTesting(NN, outputs, NB_OF_LOOPS);
      neuralLearning(NN, outputs, NB_OF_LOOPS);
      neuralTesting(NN, outputs, NB_OF_LOOPS);
      break;

    default :
      err(1, "bad argument");
      break;
    }

  return 0;
}

void neuralLearning(NeuralNetwork* NN, Outputs* outputs, unsigned int nb_of_feeding)
{
  warnx("Preparing learning : 3, 2, 1...\nENGAGE!"); 
  for (unsigned int i = 0 ; i < nb_of_feeding ; ++i)
  {
    short a = rand() % 2;
    short b = rand() % 2;
    warnx("a = %d ; b = %d\n", a, b);
    short expected_output = (a != b);

    float inputs[2] = {(float)a, (float)b};

    warnx("\n### Feeding n.%d in progress...", i);
    // FeedForward
    feedForward(NN, inputs, 2, outputs);
    warnx("\n# Feeding n.%d over", i);
    printOutputs(outputs, 0);
    
    warnx("\n### Updating n.%d of the neural network...", i);
    // Update Weight
    UpdateWeight(NN, expected_output, outputs);
    warnx("\n# Updating n.%d over.", i);
    printNeuralNetwork(NN);
    printOutputs(outputs, 0);
   
  }
  warnx("\n##### Learning complete. ######");
  printNeuralNetwork(NN);
  printOutputs(outputs, 0);
}

void neuralTesting(NeuralNetwork* NN, Outputs* outputs, unsigned int nb_of_testing)
{
  unsigned int nb_of_win = 0;
  float final_output;
  short bool_output;
  
  for (unsigned int i = 0 ; i < nb_of_testing ; ++i)
  {
    short a = rand() % 1;
    short b = rand() % 1;
    warnx("a = %d ; b = %d\n", a, b);
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
}
