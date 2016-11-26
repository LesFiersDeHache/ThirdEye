// Matrix.h //
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <assert.h>
#include <time.h>

#ifndef ONLYONCE_MATRIX
#define ONLYONCE_MATRIX

#define Uint unsigned int
#define Ulong unsigned long long

// Mat :
// Matrix structure. 
// tab : tab which contains all the values of the matrix
// xl : nbr of rows 
// yl : nbr of column
typedef struct Mat {

    float* tab;
    Uint xl;
    Uint yl;

} Mat;

// mNewFill :
// Create a new matrix, with 'xl' rows and 'yl' column, and fill
// it with 'fill'.
//
// xl : nbr of rows of the new matrix
// yl : nbr of column of the new matrix
// fill : float which what the matrix will be filled
//
// return : the new matrix
Mat* mNewFill(Uint xl, Uint yl, float fill);

// mNewRand :
// Create a new matrix, with 'xl' rows and 'yl' column, and fill it with
// random float values.
//
// xl : nbr of rows of the new matrix
// yl : nbr of columns of the new matrix 
// mult and add : the matrix will be filled with random float calculated with 
//                this formula : 
//                mult * [0.0 - 1.0] + add 
//                with [0.0 - 1.0] a float between 0.0 and 1.0
//
// return : the new matrix
Mat* mNewRand(Uint xl, Uint yl, float mult, float add);

// mGet :
// Get a value in a matrix.
//
// M : matrix which we want to pick up value
// x : row where we want to pick up the value
// y : column where we want to pick up the value
//
// return : the value that we want to pick up
float mGet(Mat* M, Uint x, Uint y);

// mSet : 
// Set a value in a matrix.
//
// M : Matrix which we want to pick up a value
// x : row where we want to pick up the value
// y : column where we want to pick up the value
//
// return : the value that we want to pick up
void mSet(Mat* M, Uint x, Uint y, float set);

// mPrint :
// Print the values of a matrix proprely
//
// M : the matrix to print
void mPrint(Mat* M);

// mPrintExt :
// Print the values of a matrix proprely, with it's size and a string.
//
// M : the matrix to print
// title : a string to print before the matrix
void mPrintExt(Mat* M, const char* title);

void mPrintDim(Mat* M, const char* title);

// mAdd :
// Create a new matrix equal to the sum of two given matrix.
//
// M1 : matrix one
// M2 : matrix two
//
// return : a matrix equal to the sum of 'M1' and 'M2'
Mat* mAdd(Mat* M1, Mat* M2);

// mSub :
// Create a new matrix equal to the substration of two given matrix.
//
// M1 : matrix one
// M2 : matrix two
//
// return : a matrix equal to the substration of 'M1' and 'M2'
Mat* mSub(Mat* M1, Mat* M2);

// mMult :
// Create a new matrix equal to the multiplication (per-to-per) 
// of two given matrix.
//
// M1 : matrix one
// M2 : matrix two
//
// return : a matrix equal to the multiplication of 'M1' and 'M2'
Mat* mMult(Mat* M1, Mat* M2);

// mDot :
// Create a new matrix equal to the dot operation of two given matrix
//
// M1 : matrix one
// M2 : matrix two
//
// return : a matrix equal to the dot operation of 'M1' and 'M2'
Mat* mDot(Mat* M1, Mat* M2);

// mSig :
// Create a new matrix where each member is equal to the sigmoid function
// of the equivalent member in the given matrix.
//
// M : Matrix 
//
// return : the new matrix equals to sigmoid(M)
Mat* mSig(Mat* M);

// mDSig :
// Create a new matrix where each member is equal to the derivate sigmoid
// function of the equivalent member in the given matrix.
//
// M : Matrix
//
// return : the new matrix equals to sigmoid'(M)
Mat* mDSig(Mat* M);

// Transposee
Mat* mT(Mat* M);

Mat* mFree(Mat* M);

void mCopyAinB(Mat* A, Mat* B);

#endif
