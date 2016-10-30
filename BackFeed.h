# include <stdlib.h>

#ifndef ONLYONCE_BITMAP
#define ONLYONCE_BITMAP

float sigmoid(float x);

float dSigmoid(float x);

float* buildErrorsArray(NeuralNetwork* NN, float out, float out2, float learning_speed);

// Use this
void UpdateWeight(NeuralNetwork* NN, float goodres, Outputs* outputs, float learning_speed);


int FindError(NeuralNetwork* NN,int layer, int num);
void reverseArray(float*tab,int len);
#endif
