# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include <err.h>

# include "Sigmoid.h"
# include "NeuralNetwork.h"

// ###### OUTPUTS STRUCT ###### //

typedef struct Outputs {

    float* tab;
    unsigned short nb_layers;
    unsigned int max_neuron;

} Outputs;

// ###### OUTPUT FUNC° ###### //

void initOutputs(Outputs* outputs, unsigned short nb_layers, unsigned int
max_neuron) {

    outputs->tab = malloc(sizeof(float) * nb_layers * max_neuron);
    outputs->nb_layers = nb_layers;
    outputs->max_neuron = max_neuron;

    for ( unsigned int i = 0 ; i < nb_layers * max_neuron ; ++i ) {
        outputs->tab[i] = -1.0;
    }

}

static void setOutput(Outputs* outputs, unsigned short layer, unsigned int neuron, float new_out) {
    outputs->tab[layer * outputs->max_neuron + neuron] = new_out;
}

float getOutput(Outputs* outputs, unsigned short layer, unsigned int neuron) {

    return outputs->tab[layer * outputs->max_neuron + neuron];
}

void printOutputs(Outputs* outputs, unsigned short begin_layer) {
    
    for ( unsigned int j = 0 ; j < outputs->max_neuron ; ++j ) {
        printf("|");
        for ( unsigned short i = begin_layer ; i < outputs->nb_layers ; ++i ) {
            printf("%f|", getOutput(outputs, i, j));
        }
        printf("\n");
    }
}

// ###### STATIC FOR FF #####//

static void fillOutputsWithInputs(float* inputs, Outputs* outputs, unsigned int
nb_inputs) {
    
    for ( unsigned int i = 0 ; i < nb_inputs ; ++i ) {
        outputs->tab[i] = inputs[i];
    }
}

// ##### FEED ONE LAYER ##### //

static float computeOutput(Outputs* outputs, NeuralNetwork* NN, unsigned short layer,
unsigned int neuron) {

    float result = 0;

    for (unsigned int i = 0 ; i < NN->nb_neurons[layer-1] ; ++i ) {
        float m = (getWeight(NN,layer, neuron, i) * getOutput(outputs, layer-1, i));
        result += m + getBiais(NN, layer, neuron);
    }
    
    return sigmoid(result);
}

static void feedOneLayer( NeuralNetwork* NN, Outputs* outputs, unsigned short layer_to_feed) {
        
    for ( unsigned int i = 0 ; i < NN->nb_neurons[layer_to_feed] ; ++i ) {
        float sig = computeOutput(outputs, NN, layer_to_feed, i);
        setOutput(outputs, layer_to_feed, i, sig);
    }
}

// ###### FEEDFORWARD ###### //

static unsigned short layerWithMaxNeurons(NeuralNetwork* NN) {

    unsigned short max = NN->nb_neurons[0];
    
    for ( unsigned int i = 1 ; i < NN->nb_layers ; i++ ) {
        if (NN->nb_neurons[i] > max) { max = NN->nb_neurons[i]; }
    }

    return max;
}

void feedForward (NeuralNetwork* NN, float* inputs, unsigned int inputs_len, Outputs* outputs) {
    
    initOutputs(outputs, NN->nb_layers, layerWithMaxNeurons(NN)); 

    assert(inputs_len <= outputs->max_neuron);
    fillOutputsWithInputs(inputs, outputs, inputs_len);
    
    for ( unsigned short i = 1 ; i < NN->nb_layers ; ++i ) {
        feedOneLayer(NN, outputs, i);
    }

}

/*
int main(){
    
    NeuralNetwork NN;
    NeuralNetwork* nn;
    
    unsigned int nb_neurons[3] = { 2, 3, 1 };
    initNeuralNetwork(nn, 3, nb_neurons);

    float inputs[2] = { 1.0, 0.0 };
    Outputs outputs_obj;
    Outputs* outputs;

    printOutputs(outputs, 0);

    feedForward(nn, inputs, 2, outputs);

    printOutputs(outputs, 0);

    //free(outputs);

    return 0;
}*/
