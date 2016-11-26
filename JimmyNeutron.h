#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <err.h>

#include "NeuralNet.h"
#include "Matrix.h"

// #### INIT #### //

NeuralNet* JnInitJn();

// #### SAVE/LOAD #### //

void JnLoadWeights(NeuralNet* JN);

void JnSaveWeights(NeuralNet* JN);

// #### LEARNING #### //

void JnLearnOneTime(NeuralNet* JN);

void JnLearn(NeuralNet* JN, const char* path, size_t loop);


