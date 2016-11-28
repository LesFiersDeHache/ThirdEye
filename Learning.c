# include <stdlib.h>
# include <err.h>
# include <assert.h>

# include "NeuralNet.h"
# include "Matrix.h"

#define NB_OF_CHAR 94
#define NB_NEURONS_L1 30

void lrnStartLearning(NeuralNet* NN, char* path, int loops) {

    // Init Input/Output
    Mat* Input = mNewFill(24*24, NB_OF_CHAR, 0.0);
    Mat* Output = mNewFill(NB_OF_CHAR, NB_OF_CHAR, 0.0);

    // Init NeuralNet
    NeuralNet* NN = NnInit(Input, Output, NB_NEURONS_L1, NB_OF_CHAR);

    // Load weights and bias
    lrnLoadNeuralNet(NN, path);

    // Begin learning
    for ( int l = 0 ; l < loops ; ++l ) {

        // Learn
        NnLearn(NN);

        // Save NeuralNet
        lrnSaveNeuralNet(NN, path);
        
        // Print current error 
        printf("Learning n.%d completed.\n", l);
        printf("Error : %f\n", NnGetError(NN));
    }
}

static void lrnSaveNeuralNet(NeuralNet* NN, char* path) {

    // FIXME
}

static void lrnLoadNeuralNet(NeuralNet* NN, char* path) {

    //FIXME
}
