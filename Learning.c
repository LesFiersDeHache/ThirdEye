# include <stdlib.h>
# include <err.h>
# include <assert.h>

# include "NeuralNet.h"
# include "Matrix.h"
# include "save.h"
# include "loadLearningImage.h"

#define NB_OF_CHAR 94
#define NB_NEURONS_L1 30

static void lrnSaveNeuralNet(NeuralNet* NN, char* path);

static void lrnLoadNeuralNet(NeuralNet* NN, char* path);

static void lrnLoadTrainingMatrix(Mat* Input, Mat* Output, char* path);

void lrnStartLearning(char* train_path, char* nn_path, int loops) {

    warnx("####################");
    warnx("# LEARNING STARTED #");
    warnx("####################");
    // Init Input/Output
    Mat* Input = mNewFill(NB_OF_CHAR, 24*24, 0.0);
    Mat* Output = mNewFill(NB_OF_CHAR, NB_OF_CHAR, 0.0);

    lrnLoadTrainingMatrix(Input, Output, train_path);

    // Init NeuralNet
    NeuralNet* NN = NnInit(Input, Output, NB_NEURONS_L1, NB_OF_CHAR);

    mFree(Input);
    mFree(Output);

    // Load weights and bias
    //lrnLoadNeuralNet(NN, nn_path);

    warnx("Let's start the leraning !");

    warnx("Begin error : %f", NnGetError(NN));

    // Begin learning
    for ( int l = 0 ; l < loops ; ++l ) {

        warnx("Learning n.%d just began.", l);

        // Learn
        NnLearn(NN);

        // Save NeuralNet
        //lrnSaveNeuralNet(NN, nn_path);
        
        // Print current error 
        warnx("Learning n.%d completed.", l);
        warnx("Error kek : %f", NnGetError(NN));
    }

    NnFree(NN);
}

void lrnInitNeuralNet(char* train_path, char* nn_path) {

    Mat* Input = mNewFill(NB_OF_CHAR, 24*24, 0.0);
    Mat* Output = mNewFill(NB_OF_CHAR, NB_OF_CHAR, 0.0);

    lrnLoadTrainingMatrix(Input, Output, train_path);

    NeuralNet* NN = NnInit(Input, Output, NB_NEURONS_L1, NB_OF_CHAR);

    mPrintDim(NN->w0to1, "Debug : lrnInitNN : W0TO1");
    mPrintDim(NN->w1to2, "Debug : lrnInitNN : W1TO2");
    //lrnSaveNeuralNet(NN, nn_path);
}

static void lrnSaveNeuralNet(NeuralNet* NN, char* path) {

    warnx("Saving Neural Network...");

    NnSave(NN->w0to1, NN->w1to2, NN->b1, NN->b2, path);

    warnx("Neural Network Saved.");
}

static void lrnLoadNeuralNet(NeuralNet* NN, char* path) {

    warnx("Loading Neural Network...");

    NnLoad(NN->w0to1, NN->w1to2, NN->b1, NN->b2, path);

    warnx("Neural Network Loaded.");
}

static void lrnLoadTrainingMatrix(Mat* Input, Mat* Output, char* path) {

    warnx("Loading Training Matrix...");

    Mat* I = learningNN(path);
    Mat* O = learningNNOutput();

    mPrintDim(I, "Loaded Input");
    mPrintDim(Input, "NN Input");
    mPrintDim(O, "Loaded Output");
    mPrintDim(Output, "NN Output");

    mCopyAinB(I, Input);
    mCopyAinB(O, Output);

    mFree(I);
    mFree(O);

    warnx("Training Matrix Loaded.");
}
