# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include <err.h>

# include "Sigmoid.h"
# include "NeuralNetwork.h"

typedef struct Outputs {

    float* tab;
    unsigned short nb_layers;
    unsigned int max_neuron;

} Outputs;


void initOutputs(Outputs* outputs, unsigned short nb_layers, unsigned int
max_neuron);


void feedForward (NeuralNetwork* NN, float* inputs, unsigned int inputs_len,
Outputs* outputs);

void printOutputs(Outputs* outputs, unsigned short begin_layer);

