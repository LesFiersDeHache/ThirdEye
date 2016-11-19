# include <stdlib.h>
# include "NeuralNetwork.h"


#ifndef ONLYONCE_SAVE
#define ONLYONCE_SAVE


void NnSave(Mat* W0, char* path);

void NnLoad();


//void floatToChar(float f, char* c);

//void save(NeuralNetwork *nn, char* biases_path, char* weights_path);

//void load(NeuralNetwork *nn, char* biases_path, char* weights_path);


#endif

