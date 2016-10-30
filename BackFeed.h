# include <stdlib.h>

#ifndef ONLYONCE_BITMAP
#define ONLYONCE_BITMAP

float sigmoid(float x);

float dSigmoid(float x);

float* buildErrorsArray(NeuralNetwork* NN, float out, float out2);

void UpdateWeight(NeuralNetwork* NN, float goodres,Outputs* outputs);


int FindError(NeuralNetwork* NN,int layer, int num);
void reverseArray(float*tab,int len);
#endif
