// Matrix.c //
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <assert.h>

#define Uint unsigned int
#define Ulong unsigned long long

typedef struct Mat {

    float* tab;
    Uint xl;
    Uint yl;

} Mat;

//mNewFill : new matrix ('xl' x 'yl'), filled with 'fill'
Mat* mNewFill(Uint xl, Uint yl, float fill) {
    
    Mat* M = malloc(sizeof(Mat));
    M->tab = malloc(sizeof(float) * xl * yl);
    M->xl = xl;
    M->yl = yl;
    
    
    for ( Ulong i = 0 ; i < xl*yl ; ++i ) {
        M->tab[i] = fill;
    }

    return M;
}

//mNewRand : new matrix ('xl' x 'yl'), filled with random values
// rand = mult * [0.0 - 1.0] + add
Mat* newNewRand(Uint xl, Uint yl, float mult, float add) {
    
    Mat* M = malloc(sizeof(Mat));
    M->tab = malloc(sizeof(float) * xl * yl);
    M->xl = xl;
    M->yl = yl;
    
    for ( Ulong i = 0 ; i < xl*yl ; ++i ) {
        //FIXME
    }

    return M;
}

// mGet : get the value of a matrix in (x;y)
float mGet(Mat* M, Uint x, Uint y) {
    return M->tab[x * M->yl + y];
}

// mSet : set the value of a matrix in (x;y)
void mSet(Mat* M, Uint x, Uint y, float set) {
    M->tab[x * M->yl + y] = set;
}

// mPrint : print matrix
void mPrint (Mat* M) {
    printf("[\n");
    for ( Uint x = 0 ; x < M->xl ; ++x ) {
        printf("[");
        for ( Uint y = 0 ; y < M->yl ; ++y ) {
            printf("%f ; ", mGet(M, x, y));
        }
        printf("]\n");
    }
    printf("]\n");
}

// mPrintExt : print matrix extanded with some values
void mPrintExt(Mat* M, const char* title) {
    printf("Matrix : '%s'\n", title);
    printf("Dimensions : %d * %d\n", M->xl, M->yl);
    mPrint(M);
    printf("\n");
}

//mAdd : addition of 2 matrix, per-a-per
Mat* mAdd(Mat* M1, Mat* M2) {
    if (M1->xl != M2->xl || M1->yl != M2->yl) {           
        err(1, "Matrix : mAdd >>> Matrix's lengths are not equal");
    }

    Mat* MR = mNewFill(M1->xl, M1->yl, 0.0);
    
    for ( Uint x = 0 ; x < M1->xl ; ++x ) {
        for ( Uint y = 0 ; y < M1->yl ; ++y ) {
            mSet(MR, x, y, mGet(M1, x, y) + mGet(M2, x, y));
        }
    }
   
    return MR;
}

// mSub : substract 2 matrix, per-to-per
Mat* mSub(Mat* M1, Mat* M2) {
    if (M1->xl != M2->xl || M1->yl != M2->yl) {
        err(1, "Matrix : mSub >>> Matrix's lengths are not equal");
    }

    Mat* MR = mNewFill(M1->xl, M1->yl, 0.0);
    
    for ( Uint x = 0 ; x < M1->xl ; ++x ) {
        for ( Uint y = 0 ; y < M1->yl ; ++y ) {
            mSet(MR, x, y, mGet(M1, x, y) - mGet(M2, x, y));
        }
    }

    return MR;
}

// mMult : mult 2 matrix, per-to-per
Mat* mMult(Mat* M1, Mat* M2) {
    if (M1->xl != M2->xl || M1->yl != M2->yl) {
        err(1, "Matrix : mMult >>> Matrix's lengths are not equal");
    }

    Mat* MR = mNewFill(M1->xl, M1->yl, 0.0);
    
    for ( Uint x = 0; x < M1->xl ; ++x ) {
        for ( Uint y = 0 ; y < M1->yl ; ++y ) {
            mSet(MR, x, y, mGet(M1, x, y) * mGet(M2, x, y));
        }
    }

    return MR;
}

Mat* mDot(Mat* M1, Mat* M2) {
    //TODO
}

int main(){
    Mat* A1 = mNewFill(4, 3, 0.0);
    Mat* A2 = mNewFill(4, 3, 1.0);
    Mat* A3 = mNewFill(4, 3, 2.0);

    printf("ADDITIONS\n");
    mPrintExt(mAdd(A1, A2), "A1 + A2");
    //mPrintExt(mAdd(A1, A3), "A1 + A3"); //Error !
    mPrintExt(mAdd(A1, mNewFill(4, 3, 2.0)), "A1 + 2.0");

    printf("SUBSTRACT\n");
    mPrintExt(mSub(A1, A2), "A1 - A2");
    mPrintExt(mSub(A1, mNewFill(4, 3, 2.0)), "A1 - 2.0");

    printf("MULTIPLY\n");
    mPrintExt(mMult(A3, A2), "A3 * A2");
    mPrintExt(mMult(A3, mNewFill(4, 3, 2.0)), "A3 * 2.0");
}
