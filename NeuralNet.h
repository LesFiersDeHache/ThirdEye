//--- NeuralNet.h ---//

#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <assert.h>

#include "Matrix.h"

#ifndef ONLYONCE_NEURALNET
#define ONLYONCE_NEURALNET

typedef struct NeuralNet {

    Mat* l0;
    Mat* l1;
    Mat* l2;

    Mat* w0to1;
    Mat* w1to2;

    Mat* b1;
    Mat* b2;

    Mat* l1_err;
    Mat* l1_delta;

    Mat* l2_err;
    Mat* l2_delta;

    Mat* out;

} NeuralNet;

NeuralNet* NnInit(Mat* X_in, Mat* Y_in,
            size_t L1_size, size_t L2_size);

void NnFree(NeuralNet* NN);

void NnLearn(NeuralNet* NN);

void matToDiag(Mat* M);

void NnFeedForward(NeuralNet* NN);

NeuralNet* NnGetXorToXorNn(size_t loop);
NeuralNet* NnGetXorNn(size_t loop);

int NnGetXorOutput(Mat* w0, Mat* w1, int input0, int input1);

//void NnPrint(NeuralNet* NN);

void NnPrettyPrint(NeuralNet* NN);

void NnBigPrint(NeuralNet* NN);

double NnGetError(NeuralNet* NN);

void THE_TEST_NN_01();

void THE_TEST_NN_02();

char* THE_TEST_NN_03();
#endif

