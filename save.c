# include <stdlib.h>
# include "NeuralNetwork.h"
# include <stdio.h>
# include <err.h>

void save(NeuralNetwork nn, char *folder_weights_path, char *folder_biaises_path)
{
	//Weights

	FILE *folder1 = NULL;
	folder1 = fopen(folder_weights_path, "w");
	
	if (folder1 == NULL)
	{
		err(0,"Weights folder has not openned properly");
	}
	else
	{
		//Write in Folder
		for (unsigned int i = 0; i < nn->size_of_weights; ++i)
		{
			fputs(weights[i],folder1);
			fputc('\n',folder1);
		}
		f.close(folder1);
	}


	//Biaises

	FILE *folder2 = NULL;
	folder2 = fopen(folder_biaises_path,"w");
	
	if (folder2 == NULL)
	{
		err(0,"Biaises folder has not oppened properly");
	}
	else
	{
		//Write in folder
		for (unsigned int i = 0; i < nn->size_of_biaises; ++i)
		{
			fputs(biaises[i],folder2);
			fputc('\n',folder2);
		}
		f.close(folder2);
	}
}


void load(NeuralNetwork nn, char *folder_weights_path, char *folder_biaises_path)
{
	//Weights

	FILE *folder1 = NULL;
	folder1 = fopen(folder_weights_path, "r");

	if (folder1 == NULL)
	{
		err(0, "Weights folder has not openned properly");
	}
	else
	{
		//Read the folder
		int line;
		while (fgets(line, 1000, file)!= NULL)
		{
			*(nn->weights) = line;
			++weights;
		}	
	}
}
