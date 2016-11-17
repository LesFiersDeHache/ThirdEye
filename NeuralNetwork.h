// NeuralNetwork.h //

#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"
#include <assert.h>
#include <err.h>

#ifndef ONLYONCE_NEURALNETWORK
#define ONLYONCE_NEURALNETWORK

// ######### STRUCTURES ######### // 

// Type : NeuralNet
// Structure which contains a neural network's matrixes
//
// nb_l : number of layers in the neural network
// L[] : array of layers matrixes
// W[] : array of weights matrixes
// B[] : array of biases matrixes

typedef struct NeuralNet {

    short nb_l;
    float learning_rate;

    Mat** L;
    Mat** W;
    Mat** B;

} NeuralNet;


// ######### INIT FUNCTIONS ######### //

// NnInit :
// Initialize an empty neural network.
//
// NN : an empty neural network
// nb_layers : number of layers of the neural network
// layers_size[] : array which contains the size
//                 of the differents layers of the
//                 neural network
//
// return : void
NeuralNet* NnInit(short nb_layers, unsigned int layers_size[]);

// ######### FREE FUNCTION ########## //

void NnFree(NeuralNet* NN);

// ######### FEEDFORWARD ######### //

void NnFeedForward(NeuralNet* NN, Mat* Inputs);

// ######### BACK PROPAGATION ######### //

void NnBackPropagation(NeuralNet* NN, Mat* Y);

// ######### PRINT FUNCTIONS ######### //

// Pretty print of a neural network
void NnPrintTotal(NeuralNet* NN);

#endif
