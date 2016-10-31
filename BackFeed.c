#include <stdio.h>
#include <math.h>
#include <err.h>
#include <stdlib.h>
#include "Sigmoid.h"
#include"FeedForward.h"
#include "BackFeed.h"
/*
float sigmoid(float x)
{
	return 1. / (1. + exp(x));
}

float dSigmoid(float x)
{
	float sig = sigmoid(x);
	return sig * (1. - sig);
}
*/

// erreur couche  = erreur couche + 1 * poids couche + 1
// last error = TrueOutput - Output


float* buildErrorsArray(NeuralNetwork* NN, float out, float out2, float learning_speed) // output = Exepected Output, trueoutput = FoundOutput
{
  //printf("error1=%2.5f\n",out);
  //printf("error2=%2.5f\n",out2);
  float lasterror = out - out2;  
  //printf("error=%2.5f\n",lasterror);
  int length = 0;
  for (short d = 0; d < NN->nb_layers; d++)    
      length += NN->nb_neurons[d];    
  float *tab = malloc(length*sizeof(float));
  tab[0] = lasterror;  
  int h = 0;
  int start = 0;  
  for(short i =NN->nb_layers-2; i >=0;i--) // place layer
    {                 
      for(int j = NN->nb_neurons[i]-1; j >= 0;j--) // place neuron ou on calcule le poids
	{	 	  
	  float somme = 0;
	  start = h; //h = position du neurone de la couche + 1 a ajouter dans le tableau;
	  for(int k = NN->nb_neurons[i + 1]-1; k >= 0;k--) // place neuron couche + 1
	    {	      
	      somme += tab[h] * getWeight(NN,i+1,k,j);	  
	      h++;		
	    }
	  h = start;	  
	  tab[h + NN->nb_neurons[i + 1] + NN->nb_neurons[i] - j-1] = somme;
	}
      h += NN->nb_neurons[i + 1];      
    }
  
  //free(tab);
  reverseArray(tab,length);
  return tab;
}

void UpdateWeight(NeuralNetwork* NN, float goodres,Outputs* outputs, float learning_speed)//expected res, my res
{
  float myres = getOutput(outputs,outputs->nb_layers-1,0);
  float* tab = buildErrorsArray(NN,goodres,myres,1.0);
  for(int i = 1; i <NN->nb_layers;i++)
    {
      //printf("-------------------------------i = %d\n",i);
      for(int j = 0;j<NN->nb_neurons[i];j++)
	{
	  //printf("-----------------------------j = %d\n",j);
	  for(int k = 0; k<NN->nb_neurons[i-1];k++)
	    {
	      //float w = getWeight(NN,i,k,j);
	      int s = FindError(NN,i,k);
	      //printf("---------------------------k = %d\n",k);
	      float nw = dSigmoid(getOutput(outputs,i-1,k))*tab[s]; 
	      //printf("new weight=%2.5f\n",nw);
	      setWeight(NN,i,j,k,nw);
	    }
	}
    }
}

int FindError(NeuralNetwork* NN,int layer, int num)
{
  int res = 0; 
  for(int i = 0;i< layer;i++)
    {
      res += NN->nb_neurons[i];
    }
  res+= num;
  return res;
}


void reverseArray(float*tab,int len)
{
  int k= len/2;
  for(int i=0;i<k;i++)
    {
      float d = tab[i];
      tab[i]= tab[len-1-i];
      tab[len-1-i] = d;
    }
}


/*int main(int argc, char *argv[])
{  
  NeuralNetwork NN;
  NeuralNetwork *nn = &NN;  
  int tab[4] = {2, 3, 3, 1};
  initNeuralNetwork(nn,4,tab);
  printNeuralNetwork(nn);
  float *tab2 = buildErrorsArray(nn,0.8,0.4);
  printf("tab0 = %3.3f\n",*tab2);
  printf("tab1 = %3.3f\n",*(tab2+1));
  printf("tab2 = %3.3f\n",*(tab2+2));
  printf("tab3 = %3.3f\n",*(tab2+3));
  printf("tab4 = %3.3f\n",*(tab2+4));
  printf("tab5 = %3.3f\n",*(tab2+5));
  printf("tab6 = %3.3f\n",*(tab2+6));  
  return 0;  
  }*/


