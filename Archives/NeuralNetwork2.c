// NeuralNetwork.c //

#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"
#include <assert.h>
#include <err.h>
#include "NeuralNetwork.h"

#define NB_L NN->nb_l
#define GL NN->L[l]
#define GL_NEXT NN->L[l+1]
#define GW NN->W[l]
#define GW_NEXT NN->WL[l+1]
#define GB NN->B[l]
#define GB_NEXT NN->B[l+1]

// ########## STRUCT NEURAL NET ########## //

typedef struct NeuralNet NeuralNet;

// ########## INIT NEURAL NET ########## //

NeuralNet* NnInit(short nb_layers, unsigned int layers_size[]) {
    
    NeuralNet* NN = malloc(sizeof(NeuralNet));
    
    NN->L = malloc(nb_layers * sizeof(Mat));
    
    NN->nb_l = nb_layers;
    
    NN->W = malloc((nb_layers - 1) * sizeof(Mat));
    NN->B = malloc(sizeof(Mat));
    
    for ( short l = 0 ; l < nb_layers ; ++l ) {
        
        NN->L[l] = mNewFill(layers_size[l], 1, 0.0);
        
        if (l < nb_layers - 1) {
        
            NN->W[l] = mNewFill(layers_size[l+1], layers_size[l], 0.5);
            NN->B[l] = mNewFill(layers_size[l+1], 1, 0.0);
            //NN->W[l] = mNewRand(layers_size[l+1], layers_size[l], 2, -1);
            //NN->B[l] = mNewRand(layers_size[l+1], 1, 2, -1);
        }
    }

    return NN;
}

// ########## FREE FUNCTION ########## //

void NnFree(NeuralNet* NN) {

    for ( short l = 0 ; l < NB_L ; ++l ) {
        
        mFree(NN->L[l]);
        
        if (l < NB_L - 1) {
        
            mFree(NN->W[l]);
            mFree(NN->B[l]);
        }
    }

    free(NN->L);
    free(NN->W);
    free(NN->B);

    free(NN);
}

// ########## FEEDFORWARD ########## //

void NnFeedForward(NeuralNet* NN, Mat* Inputs) {

    mPrintExt(NN->L[0], "Input layer");
    mCopyAinB(Inputs, NN->L[0]);

    for ( short l = 0 ; l < NB_L - 1 ; ++l ) {

        Mat* D = mDot(GW, GL);
        Mat* A = mAdd(D, GB);
        Mat* S = mSig(A);
        mCopyAinB(S, GL_NEXT);

        mFree(S);
        mFree(D);
        mFree(A);
    }
}

// ########## BACKPROPAGATION ########## //
 
// Y = wanted results (l == L) OR next layer's error (else)
static Mat* computeCurrLayerError(NeuralNet* NN, short l, Mat* Y) {

    assert(l < NN->nb_l);
    assert(l >= 0);

    if (l == NN->nb_l - 1) {

        Mat* D1 = mSub(GL, Y); // L - Y
        Mat* D = mT(D1); // (D1)^T

        mFree(D1);
        
        return D;
    }
    else {
        
        mPrintExt(GW, "GW");
        mPrintExt(Y, "Y");
        Mat* C = mDot(GW, Y); // C = W.Y

        Mat* F1 = mDSig(GL); // F1 = o'(L)
        Mat* F = mT(F1); // F = F1^T

        Mat* D = mMult(F, C); // D = F x C

        mFree(C);
        mFree(F1);
        mFree(F);

        return D;
    }
}

static Mat* computeCurrDeltaWeight(NeuralNet* NN, short l, Mat* Prev_Err) {

    assert(l < NN->nb_l - 1);
    assert(l >= 0);

    Mat* DW1 = mDot(GL, Prev_Err);
    //mPrintExt(Prev_Err, "Prev_Err");
    //mPrintExt(GL, "GL");
    //Mat* DW1 = mDot(Prev_Err, GL); // DW1 = (Prev_Err).L
    Mat* DW2 = mT(DW1); // DW2 = DW1^T
    mFree(DW1);

    Mat* M = mNewFill(DW2->xl, DW2->yl, - NN->learning_rate); // M = (-l_r)
    
    Mat* DW = mMult(M, DW2); // DW = M x DW2
    mFree(DW2);
    mFree(M);

    return DW;
}

// Return current layer's error matrix
static Mat* backPropagateOneLayer(NeuralNet* NN, short l, Mat* Prev_Error) {

    Mat* DW = computeCurrDeltaWeight(NN, l, Prev_Error);
    
    Mat* New_W = mAdd(GW, DW);
    mCopyAinB(New_W, GW);
    mFree(New_W);

    return DW;
}

void NnBackPropagation(NeuralNet* NN, Mat* Y) {

    warnx("Back : 1");

    Mat* Error = computeCurrLayerError(NN, NN->nb_l - 1, Y);

    warnx("Back : 2");

    for ( short l = NN->nb_l - 2 ; l >= 0 ; --l ) {

        warnx("Back : For %d : 1", l);

        Mat* New_Error = backPropagateOneLayer(NN, l, Error);

        warnx("Back : For %d : 2", l);

        mCopyAinB(New_Error, Error);

        warnx("Back : For %d : 3", l);

        mFree(New_Error);

        warnx("Back : For %d : 4", l);
    }
}

// ########## PRINTS ########## //

static void NnPrintLayers(NeuralNet* NN) {
    
    printf("#  LAYERS  #\n");
    
    for ( short l = 0 ; l < NB_L; ++l ) {
    
        printf("|---LAYER %d---|\n", l);
        mPrint(NN->L[l]);
    }

    printf("#  END LAYERS  #\n\n");
}

static void NnPrintOutputs(NeuralNet* NN) {
    
    printf("#  OUTPUTS  #\n");
    mPrint(NN->L[NB_L - 1]);
    printf("#  END OUTPUTS  #\n\n");
}

static void NnPrintWeights(NeuralNet* NN) {

    printf("#  WEIGHTS  #\n");
    
    for ( short l = 0 ; l < NB_L - 1; ++l ) {
    
        printf("|---WEIGHTS %d TO %d---|\n", l, l+1);
        mPrint(NN->W[l]);
    }

    printf("#  END WEIGHTS  #\n\n");
}

static void NnPrintBiases(NeuralNet* NN) {

    printf("#  BIASES  #\n");
    
    for ( short l = 0 ; l < NB_L - 1; ++l ) {
    
        printf("|---BIASES %d---|\n", l);
        mPrint(NN->B[l]);
    }

    printf("#  END WEIGHTS  #\n\n");
}

void NnPrintTotal(NeuralNet* NN) {

    printf("####################\n");
    printf("#  NEURAL NETWORK  #\n");
    printf("####################\n\n");
    
    NnPrintBiases(NN);
    NnPrintLayers(NN);
    NnPrintWeights(NN);
    NnPrintOutputs(NN);

    printf("######################\n");
    printf("# END NEURAL NETWORK #\n");
    printf("######################\n");
}
