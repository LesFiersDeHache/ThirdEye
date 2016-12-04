// Matrix.c //
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <assert.h>
#include <time.h>
#include "Sigmoid.h"

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
Mat* mNewRand(Uint xl, Uint yl, float mult, float add) {
    
    srand(time(NULL));

    Mat* M = malloc(sizeof(Mat));
    M->tab = malloc(sizeof(float) * xl * yl);
    M->xl = xl;
    M->yl = yl;
    
    for ( Ulong i = 0 ; i < xl*yl ; ++i ) {
        M->tab[i] = mult * (rand()%1000/1000.0) + add;
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
    for ( Uint x = 0 ; x < M->xl ; ++x ) {
        printf("[");
        for ( Uint y = 0 ; y < M->yl ; ++y ) {
            float n = mGet(M, x, y);
            if (n >= 0) { printf(" "); }
            printf("%f ; ", n);
        }
        printf("]");
        if (x < M->xl - 1) {
            printf("\n");
        }
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

void mPrintDim(Mat* M, const char* title) {

    printf("Matrix : '%s'\n", title);
    printf("Dimensions : %d * %d\n", M->xl, M->yl);
}

void mPrintCompact(Mat* M, const char* title) {

    printf("Matrix : '%s'\n", title);
    printf("Dimensions : %d * %d\n", M->xl, M->yl);

    for ( size_t x = 0 ; x < M->xl ; ++x ) {
        for ( size_t y = 0 ; y < M->yl ; ++y ) {

            float g = mGet(M, x, y);
            if (g < 0.0) {

                printf("-");
            }
            else if (g < 0.5) {

                printf(".");
            }
            else if (g < 0.8) {

                printf(":");
            }
            else {

                printf("1");
            }

            if (y % 24 == 23) {

                //printf("\n");
            }
        }
        printf("\n");
    }
}


//mAdd : addition of 2 matrix, per-a-per
Mat* mAdd(Mat* M1, Mat* M2) {
    if (M1->xl != M2->xl || M1->yl != M2->yl) {           
        mPrintDim(M1, "mAdd : Dim of M1");
        mPrintDim(M2, "mAdd : Dim of M2");
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
        mPrintDim(M1, "mSub : Dim of M1");
        mPrintDim(M2, "mSub : Dim of M2");
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
        mPrintDim(M1, "mMult : Dim of M1");
        mPrintDim(M2, "mMult : Dim of M2");
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

//mDot : dot operation between two matrix
//The nbr of column of the first matrix must be equal to the nbr of rows
//in the second matrix.
Mat* mDot(Mat* M1, Mat* M2) {
    if (M1->yl != M2->xl) {
        mPrintDim(M1, "mDot : Dim of M1");
        mPrintDim(M2, "mDot : Dim of M2");
        err(1, "Matrix : mDot >>> Matrix length condition is not true.\n"); 
    }

    Mat* MR = mNewFill(M1->xl, M2->yl, 0.0);
    Uint common_len = M1->yl;

    for ( Uint x = 0 ; x < M1->xl ; ++x ) {
        for ( Uint y = 0 ; y < M2->yl ; ++y ) {
            float sum = 0;
            
            for ( Uint k = 0 ; k < common_len ; ++k ) {
                sum += mGet(M1, x, k) * mGet(M2, k, y);
            }

            mSet(MR, x, y, sum);
        }
    }

    return MR;
}

//apply sigmoid 
Mat* mSig(Mat* M) {
    
    Mat* MR = mNewFill(M->xl, M->yl, 0.0);
    
    for ( Uint x = 0 ; x < M->xl ; ++x ) {
        for ( Uint y = 0 ; y < M->yl ; ++y ) {
            float value = sigmoid(mGet(M, x, y));
            mSet(MR, x, y, value);
        }
    }

    return MR;
}

Mat* mDSig(Mat* M) {

    Mat* MR = mNewFill(M->xl, M->yl, 0.0);
    
    for ( Uint x = 0 ; x < M->xl ; ++x ) {
        for ( Uint y = 0 ; y < M->yl ; ++y ) {
            float value = dSigmoid(mGet(M, x, y));
            mSet(MR, x, y, value);
        }
    }

    return MR;
}

Mat* mT(Mat* M) {

    Mat* R = mNewFill(M->yl, M->xl, 0.0);

    for ( Uint x = 0 ; x < M->xl ; ++x ) {
        for ( Uint y = 0 ; y < M->yl ; ++y ) {
            //warnx("Write M[%d,%d] at R[%d,%d].", x, y, y, x);
            mSet(R, y, x, mGet(M, x, y));
        }
    }

    return R;
}

void mFree(Mat* M) {

    free(M->tab);
    free(M);
}

void mCopyAinB(Mat* A, Mat*B) {

    if (A->xl != B->xl || A->yl != B->yl) {
        err(1, "Matrix : mCopyAinB >>> the size of A and B are not the same."); 
    }

    for ( Uint x = 0 ; x < A->xl ; ++x ) {
        for ( Uint y = 0 ; y < A->yl ; ++y ) {

            mSet(B, x, y, mGet(A, x, y));
        }
    }
}

Mat* mExtractLine(Mat* M, Uint line) {

    if (line >= M->xl) {

        warnx("Matrix : mExtractLine : line >= M->xl");
        err(1, "Assert not respected");
    }

    Mat* R = mNewFill(1, M->yl, 0.0);

    for ( Uint y = 0 ; y < M->yl ; ++y ) {

        mSet(R, 0, y, mGet(M, line, y));
    }

    return R;
}

Mat* mAddLineByLine(Mat* M, Mat* M_one_line) {

    Mat* R = mNewFill(M->xl, M->yl, 0.0);

    for ( Uint x = 0 ; x < M->xl ; ++x ) {

        for ( Uint y = 0 ; y < M->yl ; ++y ) {

            mSet(R, x, y, (mGet(M, x, y) + mGet(M_one_line, 0, y)));
        }
    }

    return R;
}

Mat* mAddAllLines(Mat* M_one_line, Mat* M) {

    Mat* R = mNewFill(M_one_line->xl, M_one_line->yl, 0.0);
    mCopyAinB(M_one_line, R);

    for ( Uint x = 0 ; x < M->xl ; ++x ) {

        for ( Uint y = 0 ; y < M->yl ; ++y ) {

            float add = mGet(R, 0, y) + mGet(M, x, y);
            mSet(R, 0, y, add);
        }
    }

    return R;
}

void mMirrorInPlace(Mat* M) {

    for ( Uint x = 0 ; x < M->xl ; ++x ) {

        for ( Uint y = 0 ; y < M->yl / 2 ; ++y ) {
        
            float tmp = mGet(M, x, y);
            mSet(M, x, y, mGet(M, x, M->yl - y - 1));
            mSet(M, x, M->yl - y - 1, tmp);
        }
    }
}
/* 
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

    Mat* A1 = mNewFill(3, 2, 2.0);
    Mat* A2 = mNewFill(2, 4, 3.0);
    Mat* A3 = mNewRand(3, 3, 2, -1);

    printf("DOT\n");
    mPrintExt(mDot(A1, A2), "A1 dot A2");
    mPrintExt(A3, "A3 rand");
}*/
