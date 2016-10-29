# include <stdlib.h>
# include <err.h>
# include <assert.h>
# include <stdio.h>
//TODO : documentation !

typedef struct NeuralNetwork {

    unsigned short nb_layers;
    unsigned int* nb_neurons;

    float* weights;
    unsigned int size_of_weights;
    float* biaises;
    unsigned int size_of_biaises;

} NeuralNetwork;

// ######### "PUBLIC" FUNCTIONS ######### //

void initNeuralNetwork(NeuralNetwork* NN, unsigned short nb_layers, unsigned int
* nb_neurons);

void loadNeuralNetwork(NeuralNetwork* NN, char* path);

float getWeight(NeuralNetwork* NN, unsigned short layer, unsigned int neuron,
unsigned int index_weight);

void setWeight(NeuralNetwork* NN, unsigned short layer, unsigned int neuron,
unsigned int index_weight, float new_weight);

void setBiais(NeuralNetwork* NN, unsigned short layer, unsigned int neuron,
float new_biais);

float getBiais(NeuralNetwork* NN, unsigned short layer, unsigned int neuron);

void prettyPrintNeuralNetwork(NeuralNetwork* NN, unsigned short min_layer);
void printNeuralNetwork(NeuralNetwork* NN);

void freeNeuralNetwork(NeuralNetwork* NN);
