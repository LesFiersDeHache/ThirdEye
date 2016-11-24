//save.c
# include <stdlib.h>
# include "NeuralNet.h"
#include "Matrix.h"
# include <stdio.h>
# include <err.h>


static void floatToChar(float f, char* tab)
{
	snprintf(tab,11,"%f",f);
}

void NnSave(Mat* W0, Mat* W1, Mat* B0, Mat* B1, char* path)
{
	FILE *folder = NULL;
	folder = fopen(path, "w");
	
	if (folder == NULL)
	{
		err(0,"FOLDER FAIL");
	}
	else
	{
		//START WRITING
		printf("WEIGHTS AND BIASES SAVING PROGRAM\n");
		printf("%s FOLDER OPENNED\n", path);
		for (unsigned int y = 0; y < W0->yl; ++y)
		{
			for (unsigned int x = 0; x < W0->xl; ++x)
			{
				char tab[11];
				floatToChar(mGet(W0,x,y),tab);
				fputs(tab,folder);
				fputc('\0',folder);
			}
		}
		fputc('\n',folder);
		printf("WO SAVED \n");


                for (unsigned int y = 0; y < W1->yl; ++y)
                {
                        for (unsigned int x = 0; x < W1->xl; ++x)
                        {       
                                char tab[9];
                                floatToChar(mGet(W1,x,y),tab);
                                fputs(tab,folder);
                                fputc('\0',folder);
                        }
                }
                fputc('\n',folder);
                printf("W1 SAVED \n");

                for (unsigned int y = 0; y < B0->yl; ++y)
                {
                        for (unsigned int x = 0; x < B0->xl; ++x)
                        {       
                                char tab[9];
                                floatToChar(mGet(B0,x,y),tab);
                                fputs(tab,folder);
                                fputc('\0',folder);
                        }
                }
                fputc('\n',folder);
                printf("BO SAVED \n");


                for (unsigned int y = 0; y < B1->yl; ++y)
                {
                        for (unsigned int x = 0; x < B1->xl; ++x)
                        {
                                char tab[9];
                                floatToChar(mGet(B1,x,y),tab);
                                fputs(tab,folder);
                               fputc('\0',folder);
                        }
                }
                fputc('\n',folder);
                printf("B1 SAVED \n");

		fclose(folder);
		printf("%s FOLDER CLOSED\n", path);
		printf("COMPLETE\n");
	}
}

/*float charToFloat(char* current)
{
	float res = 0;
	float coef = 10;
	if (current[0] == '-')
	{
		if (current[2] == '.')
		{
			coef = 1;
		}
	}
	else
	{
		if (current[1] == '.')
		{
			coef = 1;
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		if (current[i] == '.' || current[i] == '-')
		{
			++i;
		}
		res = res + ((float)current[i] - 18) * coef;
		coef/=10;
	}
	return res;
}*/

void NnLoad(Mat* W0, Mat* W1, Mat* B0, Mat* B1, char* path)
{
	int size_max = 10000;
	FILE *folder = NULL;
	folder = fopen(path, "r");
	if (folder == NULL)
	{
		err(0, "FOLDER OPENNING HAS FAILED");
	}
	else
	{
		printf("WEIGHTS AND BIAISES LOADING PROGRAM STARTED\n");
		printf("%s FOLDER OPENNED\n",path);
		//Beginning the read
		char line[10000];
		char current[13];
		int i = 0;
		int count = 0;
		fgets(line, size_max, folder);
		printf("LOADING OF W0 MATRIX\n");
		
		for (unsigned int y = 0; y < W0->yl; ++y)             //W0
		{
			for (unsigned int x = 0; x < W0->xl; ++x)
			{
		                while (line[count] != '\0')
                		{
                        		current[i] = line[count];
                        		++count;
					++i;
                		}
				current[i] = line[count];
                		++count;
				i = 0;
				mSet(W0,x,y,atof(current));
			}
		}
		count = 0;
		printf("MATRIX W0 LOADED\n");
              fgets(line, size_max, folder);
              printf("LOADING OF W1 MATRIX\n");
              for (unsigned int y = 0; y < W1->yl; ++y)             //W1
               {
                        for (unsigned int x = 0; x < W1->xl; ++x)
                        {
                                while (line[count] != '\0')
                                {
                                        current[i] = line[count];
                                        ++count;
                                        ++i;
                                }
                                current[i] = line[count];
                                ++count;
                                i = 0;
                                mSet(W1,x,y,atof(current));
                        }
                }
		count = 0;
		printf("MATRIX W1 LOADED\n");
		fgets(line,size_max,folder);
                printf("LOADING OF B0 MATRIX\n");

                for (unsigned int y = 0; y < B0->yl; ++y)         //B0
                {
                        for (unsigned int x = 0; x < B0->xl; ++x)
                        {
                                while (line[count] != '\0')
                                {
                                        current[i] = line[count];
                                        ++count;
                                        ++i;
                                }
                                current[i] = line[count];
                                ++count;
                                i = 0;
                                mSet(B0,x,y,atof(current));
                        }
                }
		count = 0;
                printf("MATRIX B0 LOADED\n");
		fgets(line,size_max,folder);
                printf("LOADING OF B1 MATRIX\n");
                for (unsigned int y = 0; y < B1->yl; ++y)     //B1
                {
                        for (unsigned int x = 0; x < B1->xl; ++x)
                        {
                                while (line[count] != '\0')
                                {
                                        current[i] = line[count];
                                        ++count;
                                        ++i;
                                }
                                current[i] = line[count];
                                ++count;
                                i = 0;
                                mSet(B1,x,y,atof(current));
                        }
                }
                printf("MATRIX B1 LOADED\n");
	}
	fclose(folder);
        printf("%s FOLDER CLOSED\n", path);
	printf("ALL MATRIX LOCK AND LOADED. LAUNCH JIMMY\n");
}

/*
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
}*/
