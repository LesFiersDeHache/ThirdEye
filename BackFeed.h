# include <stdlib.h>

#ifndef ONLYONCE_BITMAP
#define ONLYONCE_BITMAP

float sigmoid(float x);

float dSigmoid(float x);

float* buildErrorsArray(NeuralNetwork* NN, float out, float out2);

#endif
