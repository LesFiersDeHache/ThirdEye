# include <stdlib.h>
# include <stdio.h>
# include "NeuralNet.h"


#ifndef ONLYONCE_SAVE
#define ONLYONCE_SAVE


void NnSave(Mat* W0, Mat* W1, Mat* B0, Mat* B1, char* path);

float charToFloat(char* current);

void NnLoad(Mat* W0, Mat* W1, Mat* B0, Mat* B1, char* path);


//void floatToChar(float f, char* c);

//void save(NeuralNetwork *nn, char* biases_path, char* weights_path);

//void load(NeuralNetwork *nn, char* biases_path, char* weights_path);


#endif

