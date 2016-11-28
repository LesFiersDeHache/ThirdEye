# include <stdlib.h>
# include <err.h>
# include <assert.h>

# include "NeuralNet.h"
# include "Matrix.h"

#define NB_OF_CHAR 94
#define NB_NEURONS_L1 30

void lrnStartLearning(NeuralNet* NN, char* path, int loops) {

    printf("####################\n");
    printf("# LEARNING STARTED #\n");
    printf("####################\n");
    // Init Input/Output
    Mat* Input = mNewFill(24*24, NB_OF_CHAR, 0.0);
    Mat* Output = mNewFill(NB_OF_CHAR, NB_OF_CHAR, 0.0);

    lrnLoadTrainingMatrix(Input, Output);

    // Init NeuralNet
    NeuralNet* NN = NnInit(Input, Output, NB_NEURONS_L1, NB_OF_CHAR);

    // Load weights and bias
    lrnLoadNeuralNet(NN, path);

    warnx("Let's start the leraning !");

    // Begin learning
    for ( int l = 0 ; l < loops ; ++l ) {

        warnx("Learning n.%d just began.", l);

        // Learn
        NnLearn(NN);

        // Save NeuralNet
        lrnSaveNeuralNet(NN, path);
        
        // Print current error 
        warnx("Learning n.%d completed.", l);
        warnx("Error : %f", NnGetError(NN));
    }
}

static void lrnSaveNeuralNet(NeuralNet* NN, char* path) {

    warnx("Saving Neural Network...");
    // FIXME
    warnx("Neural Network Saved.");
}

static void lrnLoadNeuralNet(NeuralNet* NN, char* path) {

    warnx("Loading Neural Network...");
    // FIXME
    warnx("Neural Network Loaded.");
}

static void lrnLoadTrainingMatrix(Mat* Input, Mat* Output) {

    warnx("Loading Training Matrix...");
    // FIXME
    warnx("Training Matrix Loaded.");
}
