#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float sigmoid(float z)
{
	return 1 / (1 + exp(-z));
}

float dSigmoid(float x)
{
	//float sig = sigmoid(x);
	//return sig * (1 - sig);
    return x * (1 - x);
}

