# include <stdlib.h>
# include <err.h>
# include <assert.h>
# include <stdio.h>

// ############################## STRUCT #####################################//


/* struct NeuralNetwork
A NeuralNetwork struct contains all the useful information about a neural
network : 
- nb_layers = the number of layers that the neural network contains (input layer
included)
- nb_neurons[] = tab of the number of neurons of each layers (nb_neurons[0] is
the number of inputs of the NN)
- weights[] = tab of the neural network's weights
- size_of_weights = size of weights[]
- biaises[] = tab of the neural network's biaises
- size_of_biaises = size of biaises[]
*/
typedef struct NeuralNetwork {
    
    unsigned short nb_layers;
    unsigned int* nb_neurons;

    float* weights;
    unsigned int size_of_weights;
    float* biaises;
    unsigned int size_of_biaises;

} NeuralNetwork;

// ################ CONSTRUCTION AND INITILIZATION FUNCTIONS #################//


//return a random weight
static float randomWeight() {
    return ((float)(rand() % 1000)) / ((float)(1000));
}

//return a random biais
static float randomBiaises() {
    //TODO
    return 0.0;
}

/* initNeuralNetwork
Initialize a new NeuralNetwork structure.
NN = NeuralNetwork to initialize

Inputs :
- nb_layers = the number of layers that the NN has.
- nb_neurons[] = tab of the number of neurons of each layers (nb_neurons[0] is the
- number of inputs of the NN)

Outputs :
- void
*/
void initNeuralNetwork(NeuralNetwork* NN, unsigned short nb_layers, 
unsigned int* nb_neurons) {

    // warnx("init : 1");

    unsigned int size_of_weights = 0;
    unsigned int size_of_biaises = 0;

    //Compute the size of the weights tab and the biaises tab
    for ( unsigned short i = 1 ; i <= nb_layers ; ++i ) {
        size_of_weights += nb_neurons[i-1] * nb_neurons[i];
        size_of_biaises += nb_neurons[i];
    }
   
    //warnx("init : 2");

    //Set NN variables
    //NN->nb_layers = malloc(sizeof(unsigned short));
    NN->nb_layers = nb_layers;

    //warnx("init 2.1");

    //Set nb_neurons tab
    NN->nb_neurons = malloc(nb_layers * sizeof(unsigned int));
    for (unsigned short i = 0 ; i < nb_layers ; ++i) {
        NN->nb_neurons[i] = nb_neurons[i];
    }

    //warnx("init : 3");

    //Allocate memory for weights tab
    NN->weights = malloc(sizeof(float) * size_of_weights);

    //warnx("init : 4");

    if ( NN->weights == NULL ) {
        err(0, "Allocation problem : malloc failed to initialize NN->weights");
    }

    //warnx("init : 5");

    NN->size_of_weights = size_of_weights;
    
    //warnx("init : 6");

    //Allocate memory for biaises tab
    NN->biaises = malloc(sizeof(unsigned int) * size_of_biaises);
    
    //warnx("init : 7");

    if ( NN->biaises == NULL ) {
        err(0, "Allocation problem : malloc failed to initialize NN->biaises");
    }
    
    //warnx("init : 8");

    NN->size_of_biaises = size_of_biaises;
    
    //warnx("init : 9");

    //Initialize weights tab with random weights
    for ( unsigned int i = 0 ; i < size_of_weights ; ++i ) {
        NN->weights[i] = randomWeight();
    }

    //warnx("init : 10");
    
    //Initialize biaises tab with random biaises
    for ( unsigned int i = 0 ; i < size_of_biaises ; ++i ) {
        NN->biaises[i] = randomBiaises();    
    }

    //warnx("init : 11");
}

// ############################## LOAD NEURAL NETWORK #########################//

void loadNeuralNetwork(NeuralNetwork* NN, char* path) {
    //TODO
}

// ############################## GET/SET #####################################//



//Return the number of weights of a neuron in a layer
static unsigned int getNbOfWeights(NeuralNetwork* NN, unsigned short layer) {
    
    //Debug
    assert(layer < NN->nb_layers);

    return NN->nb_neurons[layer - 1];
}

//Return the global index of a weight in the weights tab 
static unsigned int getIndex(NeuralNetwork* NN, unsigned short layer, 
unsigned int neuron, unsigned int index_weight) { 

    //Debug
    assert(layer < NN->nb_layers);
    assert(neuron < NN->nb_neurons[layer]);
    assert(index_weight < NN->nb_neurons[layer - 1]);
    
    unsigned int index = 0;
    
    for ( unsigned short i = 1 ; i < layer ; ++i ) {
        index += NN->nb_neurons[i - 1] * NN->nb_neurons[i];
    }

    index += NN->nb_neurons[layer] * neuron + index_weight;

    return index;
}

/* getWeight
Return the value a weight.

Input :
- *NN = the weight's neural network
- layer = layer of the weight's neuron
- neuron = weight's neuron
- index_weight = "local" index of the weight (the n-th weight of the neuron)

Output :
- weight's value
*/
float getWeight(NeuralNetwork* NN, unsigned short layer, unsigned int neuron,
unsigned int index_weight) {
    
    return NN->weights[getIndex(NN, layer, neuron, index_weight)];
}

/* setWeight
Set the value of a weight.

Input :
- *NN = the weight's neural network
- layer = layer of the weight's neuron
- neuron = weight's neuron
- index_weight = "local" index of the weight (the n-th weight of the neuron)
- new_weight = new value of the weight

Output :
- void
*/
void setWeight(NeuralNetwork* NN, unsigned short layer, unsigned int neuron,
unsigned int index_weight, float new_weight) {

    NN->weights[getIndex(NN, layer, neuron, index_weight)] = new_weight;
}


void setBiais(NeuralNetwork* NN, unsigned short layer, unsigned int neuron,
float new_biais) {
    
    //TODO
}

float getBiais(NeuralNetwork* NN, unsigned short layer, unsigned int neuron) {
    //TODO
    return 0.0;
}

// ############################## PRINT NEURAL NET ###################################//

void printNeuralNetwork(NeuralNetwork* NN) {

    for ( short i = 1 ; i < NN->nb_layers; ++i ) {
        printf("Layer %d\n", i);
        
        for ( unsigned int j = 0 ; j < NN->nb_neurons[i] ; ++j ) {
            printf("|----Neuron n°%d : ", j);

            for ( unsigned int k = 0 ; k < getNbOfWeights(NN, i); k++ ) {
                printf("w(%d) = %f ; ", k, getWeight(NN, i, j, k));
            }

            printf("|\n");
        }
        printf("\n");
    }
}

// ############################## FREE STRUCTURE #####################################//

/* freeNeuralNetwork
Free memory used by the neural network.
Call this function on a neural network when you will not use it anymore.

Input :
- NN = Neural Network that you want to free.

Output :
- void
*/
void freeNeuralNetwork(NeuralNetwork* NN) {
    //TODO
}

