# include <stdlib.h>
# include <err.h>
# include <assert.h>

# include "NeuralNet.h"
# include "Matrix.h"
# include "save.h"
# include "loadLearningImage.h"

#define NB_OF_CHAR 94
#define NB_NEURONS_L1 3

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
    lrnLoadNeuralNet(NN, nn_path);

    warnx("Let's start the leraning !");

    warnx("Begin error : %f", NnGetError(NN));

    // Begin learning
    for ( int l = 0 ; l < loops ; ++l ) {

        // Learn
        NnLearn(NN);

        if (l % 1000 == 0) {
            
            float per = ((float)l / (float)loops) * 100.0;
            warnx("%f percent > Error : %.15f", per, NnGetError(NN));
            lrnSaveNeuralNet(NN, nn_path);            
        }
    }

    lrnSaveNeuralNet(NN, nn_path);
    NnBigPrint(NN);
    NnFree(NN);
}

void lrnInitNeuralNet(char* train_path, char* nn_path) {

    Mat* Input = mNewFill(NB_OF_CHAR, 24*24, 0.0);
    Mat* Output = mNewFill(NB_OF_CHAR, NB_OF_CHAR, 0.0);

    lrnLoadTrainingMatrix(Input, Output, train_path);

    NeuralNet* NN = NnInit(Input, Output, NB_NEURONS_L1, NB_OF_CHAR);

    mPrintDim(NN->w0to1, "Debug : lrnInitNN : W0TO1");
    mPrintDim(NN->w1to2, "Debug : lrnInitNN : W1TO2");
    lrnSaveNeuralNet(NN, nn_path);

    NnBigPrint(NN);
}

char* getCharFromMat(Mat* I) {

    mPrintDim(I, "GET CHAR : I");

    char* result = malloc(sizeof(char) * I->xl);

    Mat* P_Out = mNewFill(I->xl, 94, 0.0);

    mPrintDim(P_Out, "GET CHAR : P_Out");

    warnx("getCharFromMat : 1");

    //lrnLoadTrainingMatrix(I, P_Out, "ascii6.bmp");

    warnx("getCharFromMat : 2");

    NeuralNet* NN = NnInit(I, P_Out, NB_NEURONS_L1, 94);

    mPrintDim(NN->w1to2, "GET CHAR : 2");

    warnx("getCharFromMat : 2");

    NnLoad(NN->w0to1, NN->w1to2, NN->b1, NN->b2, "save.txt");

    warnx("getCharFromMat : 3");

    NnFeedForward(NN);

    warnx("getCharFromMat : 4");

    Mat* R = NN->l2;
    mPrintCompact(R, "R");

    for ( size_t x = 0 ; x < R->xl ; ++x ) {
        
        size_t i = 0;

        while (i < R->yl && mGet(R, x, i) < 0.7) {

            i++;
        }

        if (i >= R->yl || i == 1) {

            result[i] = ' ';
        }
        else if (i == 0) {

            result[i] = '!';
        }
        else {

            result[i] = 33 + i;
        }

        warnx("getCharFromMat : %ld = %c", i, result[i]);
    }

    warnx("getCharFromMat : e");
  
    NnFree(NN);
  
    warnx("getCharFromMat : 1.e");

    warnx("getCharFromMat : 2.e");

    mFree(P_Out);
    
    warnx("getCharFromMat : 3.e");

    return result;
}

// #########################################################

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
