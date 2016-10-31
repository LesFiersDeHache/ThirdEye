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

Mat* newMat(Uint x_len, Uint y_len, float fill);

Mat* newMatRandom(Uint x_len, Uint y_len, float mult, float add);

void freeMat(Mat* mat);

float getInMat(Mat* mat, Uint x, Uint y) {
    assert(x, y, mat->x_len, mat->y_len);
    return mat->tab[x * mat->y_len + y];
}

//Set value
void setInMat(Mat* mat, Uint x, Uint y, float new_value) {
    assert(x, y, mat->x_len, mat->y_len);
    mat->tab[x * mat->y_len + y] = new_value;
}

//Get len X
Uint getLenXMat(Mat* mat) {
    return mat->x_len;
}

//Get len Y
Uint getLenYMat(Mat* mat) {
    return mat->y_len;
}

void printMat(Mat* mat);

Mat* ope_Mcopy(Mat* mat);

Mat* ope_MpR(Mat* mat, float r);

Mat* ope_MxR(Mat* mat, float r);

Mat* ope_MpM(Mat* mat1, Mat* mat2);

Mat* ope_MxM(Mat* mat1, Mat* mat2);

Mat* ope_MdotM(Mat* mat1, Mat* mat2);

Mat* ope_VdotM(Mat* vect, Mat* mat);

Mat* ope_VdotV(Mat* vect1, Mat* vect2);

Mat* ope_Mt(Mat* mat);

Mat* ope_apply_sigmoid(Mat* mat);

Mat* ope_apply_deriv_sigmoid(Mat* mat);


