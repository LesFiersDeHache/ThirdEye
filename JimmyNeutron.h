#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <err.h>

#include "NeuralNet.h"
#include "Matrix.h"

// #### INIT #### //

NeuralNet* JnInitJn();

// #### SAVE/LOAD #### //

void JnLoadWeights(JN, path);

void JnSaveWeights(JN, path);

// #### LEARNING #### //

void JnLearnOneTime(NeuralNet* JN);

void JnLearn(NeuralNet* JN, const char* path, size_t loop);


