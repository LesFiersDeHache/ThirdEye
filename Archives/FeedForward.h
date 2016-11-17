# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include <err.h>

# include "Sigmoid.h"
# include "NeuralNetwork.h"

// ############### OUTPUTS STRUCT ################# //

// Outputs struct
// Contains outputs of a feed forward.
// - tab : tab of outputs
// - nb_layers : nbr of layers of the NeuralNetwork at the origin of the outputs
// - max_neuron : maximum of layer in a single layer of the NeuralNetwork at the
//                origin of the outputs
#ifndef ONLYONCE_FEEDFORWARD
#define ONLYONCE_FEEDFORWARD
typedef struct Outputs {

    float* tab;
    unsigned short nb_layers;
    unsigned int max_neuron;

} Outputs;

// getOutput
// Get the output of a neuron
// - outputs : the outputs struct pointer
// - layer : the layer of the neuron which we want the output
// - neuron : index of the neuron in his layer
//
// return : output value of the neuron
float getOutput(Outputs* outputs, unsigned short layer, unsigned int neuron);

// ###### INIT ##### //


// DONT USE THIS
void initOutputs(Outputs* outputs, unsigned short nb_layers, unsigned int
max_neuron);

// FeedForward function
// Do the feed forward and stock the outputs in a Outputs struct.
// - NN : NeuralNetwork (already initialized) pointer
// - inputs : tab of inputs to give to the neural network
// - inputs_len : nbr of inputs
// - outputs : Outputs struct (not initialized) pointer
//
// return : void
void feedForward (NeuralNetwork* NN, float* inputs, unsigned int inputs_len,
Outputs* outputs);

// printOutputs
// Print the outputs struct.
// - outputs : Outputs struct (already initialized) pointer
// - begin_layer : start printing at this layer
void printOutputs(Outputs* outputs, unsigned short begin_layer);

#endif
