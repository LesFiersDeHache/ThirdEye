#include <stdio.h>
#include <math.h>
#include"NeuralNetwork.h"

float sigmoid(float x)
{
	return 1. / (1. + exp(x));
}

float dSigmoid(float x)
{
	float sig = sigmoid(x);
	return sig * (1. - sig);
}
// erreur couche  = erreur couche + 1 * poids
// last error = TrueOutput - Output

int* buildErrorsArray(NeuralNetwork NN, float out, float out2) // output = Exepected Output, trueoutput = FoundOutput
{
  float lasterror = out - out2;
  int length = 0;
  for (int k = 0; k < NN->nb_layers; k++)
    {
      length += NN->nb_neurons[k];
    }
  int*tab = malloc(length*sizeof(int));
  tab[0] = lasterror;
  int h = 1;
  int start = 0;
  unsigned int w = 0;
  for(unsigned int i =NN->nb_layer-1; i >0;i--) // place layer
    {      
      for(unsigned int j = NN->nb_neurons[i]; j > 0;j--) // place neuron ou on calcule le poids
	{
	  int somme = 0;
	  start = h; //h = position du neurone de la couche + 1 a ajouter dans le tableau;
	  for(unsigned int k = NN->nb_neurons[i + 1]; k > 0;k--) // place neuron couche + 1
	    {
	      somme += tab[h] * getWeigth(NN,i,j,k);
	      h++;		
	    }
	  h = start;
	  tab[h + NN->nb_neurons[i + 1] + NN->nb_neurons[i] - j] = somme;
	}
      h += NN->nb_neurons[i + 1];
    }
  //free(tab);
  return tab;
}

