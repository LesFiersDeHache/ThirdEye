#include <stdlib.h>
#include <err.h>
#include <assert.h>

#include "save.h"
#include "Matrix.h"
#include "NeuralNet.h"
#include "loadLearningImage.h"

#ifndef ONLYONCE_LEARNING_X
#define ONLYONCE_LEARNING_X

void lrnStartLearning(char* train_path, char* nn_path, int loops);

void lrnInitNeuralNet(char* train_path, char* nn_path);

char* getCharFromMat(Mat* I);

#endif
