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

static void setOutput(Outputs* outputs, unsigned short layer, unsigned int
neuron, float new_out);

static float computeOutput(Outputs* outputs, NeuralNetwork* NN, unsigned short
layer,
unsigned int neuron);

static void feedOneLayer( NeuralNetwork* NN, Outputs* outputs, unsigned short
layer_to_feed);

static unsigned short layerWithMaxNeurons(NeuralNetwork* NN);

void feedForward (NeuralNetwork* NN, float* inputs, unsigned int inputs_len,
Outputs* outputs);



