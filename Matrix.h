#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <err.h>
#define Uint unsigned int
#define Ulong unsigned long long

typedef struct Mat {

    Uint x_len;
    Uint y_len;
    float* tab;

} Mat;

//INIT
Mat* newMat(Uint x_len, Uint y_len, float fill);

Mat* newMatRandom(Uint x_len, Uint y_len, float mult, float add);

//FREE
void freeMat(Mat* mat);

//GET / SET
float getInMat(Mat* mat, Uint x, Uint y); 

void setInMat(Mat* mat, Uint x, Uint y, float new_value); 

Uint getLenXMat(Mat* mat);

Uint getLenYMat(Mat* mat);

//PRINT
void printMat(Mat* mat);

//OPERATIONS
//All these functions does not modity the matrix in entry
Mat* ope_Mcopy(Mat* mat); //Copy a Mat

Mat* ope_MpR(Mat* mat, float r); //Matrix + Real

Mat* ope_MxR(Mat* mat, float r); //Matrix * Real

Mat* ope_MpM(Mat* mat1, Mat* mat2); //Matrix + Matrix

Mat* ope_MxM(Mat* mat1, Mat* mat2); //Matrix * Matrix (classic mult 1 by 1)

Mat* ope_MdotM(Mat* mat1, Mat* mat2); //Matrix dot Matrix
                                      //(Matrix multiplication)

//Vector : one dimensionnal matrix (vertical or horizontal)
Mat* ope_VdotM(Mat* vect, Mat* mat); //Vector dot Matrix

Mat* ope_VdotV(Mat* vect1, Mat* vect2); //Vector dot Vector

Mat* ope_Mt(Mat* mat); //Matrix transpose

Mat* ope_apply_sigmoid(Mat* mat); //Apply sigmoid function to Matrix

Mat* ope_apply_deriv_sigmoid(Mat* mat); //Apply derivate sigmoid function
                                        //to Matrix


