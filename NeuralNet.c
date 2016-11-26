//--- NeuralNet.c ---//

#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <assert.h>
#include "NeuralNet.h"

#include "Matrix.h"

#define L0 NN->l0
#define L1 NN->l1
#define L2 NN->l2

#define W0to1 NN->w0to1
#define W1to2 NN->w1to2

#define B1 NN->b1
#define B2 NN->b2

#define L1_ERR NN->l1_err
#define L1_DELTA NN->l1_delta

#define L2_ERR NN->l2_err
#define L2_DELTA NN->l2_delta

#define OUT NN->out

// ### STRUCT NEURAL NET ### //

typedef struct NeuralNet NeuralNet;

// ### NEURAL NET INIT ### //

NeuralNet* NnInit(Mat* X_in, Mat* Y_in,
            size_t L1_size, size_t L2_size) {
    
    // Allocation
    NeuralNet* NN = malloc(sizeof(NeuralNet));


    // Layer 0 init
    L0 = mNewFill(X_in->xl, X_in->yl, 0.0);
    mCopyAinB(X_in, L0);

    // Weights init (to random values)
    
    //W0to1 = mNewFill(X_in->yl, L1_size, 0.5);
    //W1to2 = mNewFill(L1_size, L2_size, 0.5);
    W0to1 = mNewRand(X_in->yl, L1_size, 2, -1);
    W1to2 = mNewRand(L1_size, L2_size, 2, -1);

    // Other layers init
    L1 = mNewFill(X_in->xl, W0to1->yl, 0.0);
    L2 = mNewFill(Y_in->xl, Y_in->yl, 0.0);

    // Expected output init
    OUT = mNewFill(Y_in->xl, Y_in->yl, 0.0);
    mCopyAinB(Y_in, OUT);

    // Biases init (to random values)
    B1 = mNewRand(L1->xl, L1->yl, 2, -1);
    B2 = mNewRand(L2->xl, L2->yl, 2, -1);

    // Error and delta of L1 matrix init
    L1_ERR = mNewFill(Y_in->xl, W1to2->xl, 0.0);
    L1_DELTA = mNewFill(X_in->xl, W0to1->yl, 0.0);

    // Error and delta of L2 matrix init
    L2_ERR = mNewFill(Y_in->xl, Y_in->yl, 0.0);
    L2_DELTA = mNewFill(Y_in->xl, Y_in->yl, 0.0);

    return NN;
}

// ### NEURAL NET FREE ### //

void NnFree(NeuralNet* NN) {

    mFree(L0);
    mFree(L1);
    mFree(L2);
    mFree(OUT);
    mFree(W0to1);
    mFree(W1to2);
    mFree(B1);
    mFree(B2);
    mFree(L1_ERR);
    mFree(L1_DELTA);
    mFree(L2_ERR);
    mFree(L2_DELTA);

    free(NN);
}

// ### NEURAL NET LEARN ### //

static void set_l1(NeuralNet* NN) {

    // L1 = sigmoid(L0 . W0to1)
    Mat* tmp = mDot(L0, W0to1);
    Mat* tmp2 = mAdd(tmp, B1);

    //mPrintExt(tmp, "l0 dot w0to1");

    Mat* M1 = mSig(tmp2);

    //mPrintExt(M1, "mSig (l0 dot w0to1)");

    mCopyAinB(M1, L1);

    //mPrintExt(L1, "l1");

    mFree(M1);
    mFree(tmp);
    mFree(tmp2);

    
}

static void set_l2(NeuralNet* NN) {

    // L2 = sigmoid(L1 . W1to2)
    Mat* tmp = mDot(L1, W1to2);
    Mat* tmp2 = mAdd(tmp, B2);

    //mPrintExt(tmp, "l1 dot w1to2");

    Mat* M2 = mSig(tmp2);

    //mPrintExt(M2, "sig(l1 dot w1to2");

    mCopyAinB(M2, L2);

    //mPrintExt(L2, "l2");

    mFree(M2);
    mFree(tmp);
    mFree(tmp2);
}

static void NnFeedForward(NeuralNet* NN) {

    set_l1(NN);

    set_l2(NN);
}

static void set_l2_Error(NeuralNet* NN) {
    
    // L2_ERR = OUT - L2
    Mat* tmp = mSub(OUT, L2);

    //mPrintExt(tmp, "out - l2");

    mCopyAinB(tmp, L2_ERR);

    //mPrintExt(L2_ERR, "l2_err");

    mFree(tmp);
}

static void set_l2_Delta(NeuralNet* NN) {

    // L2_DELTA = L2_ERR * dsigmoid(L2)
    Mat* tmp = mDSig(L2);

    //mPrintExt(tmp, "sig'(l2)");

    Mat* tmp2 = mMult(L2_ERR, tmp);

    //mPrintExt(tmp2, "l2_err * sig'(l2)");

    mCopyAinB(tmp2, L2_DELTA);

    //mPrintExt(L2_DELTA, "l2_delta");

    mFree(tmp);
    mFree(tmp2);
}

static void set_l1_Error(NeuralNet* NN) {
    
    // L1_ERR = L2_DELTA . (W1to2)^T
    Mat* tmp = mT(W1to2);

    //mPrintExt(tmp, "W1to2.T");

    Mat* tmp2 = mDot(L2_DELTA, tmp);

    //mPrintExt(tmp2, "l2_delta dot W1to2.T");

    mCopyAinB(tmp2, L1_ERR);

    //mPrintExt(L1_ERR, "l1_err");

    mFree(tmp);
    mFree(tmp2);
}

static void set_l1_Delta(NeuralNet* NN) {

    // L1_DELTA = L1_ERR * dsigmoid(L1)
    Mat* tmp = mDSig(L1);

    //mPrintExt(tmp, "sig'(l1)");

    Mat* tmp2 = mMult(L1_ERR, tmp);

    //mPrintExt(tmp2, "l1_err * sig'(l1)");

    mCopyAinB(tmp2, L1_DELTA);

    //mPrintExt(L1_DELTA, "l1_delta");

    mFree(tmp);
    mFree(tmp2);
}

static void update_w1to2(NeuralNet* NN) {

    // W1to2 = W1to2 + [ (L1)^T . L2_DELTA ]
    Mat* tmp1 = mT(L1);

    //mPrintExt(tmp1, "l1.T");

    Mat* tmp2 = mDot(tmp1, L2_DELTA);

    //mPrintExt(tmp2, "l1.T dot l2_delta");

    Mat* tmp3 = mAdd(W1to2, tmp2);

    //mPrintExt(tmp3, "w1to2 + l1.T dot l2_delta");

    mCopyAinB(tmp3, W1to2);

    //mPrintExt(W1to2, "w1to2");

    mFree(tmp1);
    mFree(tmp2);
    mFree(tmp3);
}

static void update_w0to1(NeuralNet* NN) {

    // W0to1 = W0to1 + [ (L1)^T . L2_DELTA ]
    Mat* tmp1 = mT(L0);

    //mPrintExt(tmp1, "l0.T");

    Mat* tmp2 = mDot(tmp1, L1_DELTA);

    //mPrintExt(tmp2, "l1.T dot l1_delta");
    
    Mat* tmp3 = mAdd(W0to1, tmp2);

    //mPrintExt(tmp3, "w0to1 + (l1.T dot l1_delta)");

    mCopyAinB(tmp3, W0to1);

    //mPrintExt(W0to1, "w0to1");

    mFree(tmp1);
    mFree(tmp2);
    mFree(tmp3);
}

static void update_b1(NeuralNet* NN) {

    Mat* tmp = mAdd(B1, L1_DELTA);
    mCopyAinB(tmp, B1);

    mFree(tmp);
}

static void update_b2(NeuralNet* NN) {

    Mat* tmp = mAdd(B2, L2_DELTA);
    mCopyAinB(tmp, B2);

    mFree(tmp);
}

static void NnBackPropagation(NeuralNet* NN) {

    //warnx("Backprog : Begin");

    set_l2_Error(NN);
    //warnx("BP : 1");

    set_l2_Delta(NN);
    //warnx("BP : 2");

    set_l1_Error(NN);
    //warnx("BP : 3");

    set_l1_Delta(NN);
    //warnx("BP : 4");

    update_w1to2(NN);
    //warnx("BP : 5");

    update_w0to1(NN);
    //warnx("BP : 6");

    update_b1(NN);

    update_b2(NN);
}

void NnLearn(NeuralNet* NN) {

    NnFeedForward(NN);

    NnBackPropagation(NN);
}

NeuralNet* NnGetXorNn( size_t loop ) {

    Mat* Input = mNewFill(4, 2, 0.0);
    Mat* Output = mNewFill(4, 1, 0.0);

    mSet(Input, 1, 1, 1.0);
    mSet(Input, 2, 0, 1.0);
    mSet(Input, 3, 0, 1.0);
    mSet(Input, 3, 1, 1.0);

    mSet(Output, 1, 0, 1.0);
    mSet(Output, 2, 0, 1.0);

    NeuralNet* NN = NnInit(Input, Output, 3, 1);

    for ( size_t l = 0 ; l < loop ; ++l ) {

        NnLearn(NN);
        
        if (l % 1000 == 0) {
            
            warnx("Error : %f", NnGetError(NN));
        }
    }
    
    mFree(Input);
    mFree(Output);

    return NN;
}

int NnGetXorOutput(Mat* w0, Mat* w1, int input0, int input1) {

    Mat* Input = mNewFill(1, 2, 0.0);
    mSet(Input, 0, 0, input0);
    mSet(Input, 0, 1, input1);

    Mat* tmp1 = mDot(Input, w0);
    Mat* l1 = mSig(tmp1);

    Mat* tmp2 = mDot(l1, w1);
    Mat* out = mSig(tmp2);

    assert(out->xl == 1 && out->yl == 1);

    int result = mGet(out, 0, 0) > 0.5;

    mFree(Input);
    mFree(tmp1);
    mFree(l1);
    mFree(tmp2);
    mFree(out);

    return result;
}
// ### PRINTS ### // 

static void NnPrint(NeuralNet* NN) {

    printf("################################\n");
    printf("##      NEURAL     NETWORK    ##\n");
    printf("################################\n\n");
    mPrintExt(L0, "Layer 0 :");

    mPrintExt(W0to1, "Weights of layers 0 to 1 :");
    mPrintExt(B1, "Biases of the layer 1 :");
    mPrintExt(L1, "Layer 1 :");

    mPrintExt(W1to2, "Weights of layers 1 to 2 :");
    mPrintExt(B2, "Biases of the layer 2 :");
    mPrintExt(L2, "Output (layer 2) :");
    mPrintExt(OUT, "Expected Output :");
}

static void printTitle(char* const chr, size_t len) {

    printf("|_");
    printf("%s", chr);
    for (size_t i = 0 ; i < (9 * len) - 7 ; ++i) {
        printf("_");
    }
    printf("| ");
}

static void printCell(float cell){

    printf("%7.3f |", cell);
}

static void printRow(Mat* M, size_t row) {

    if (row < M->xl) {
    
        printf("|");
        for ( size_t y = 0 ; y < M->yl ; ++y ) {

            printCell(mGet(M, row, y));
        }
        printf(" ");
    }
    else if (row == M->xl) {

        printf("\"");
        for ( size_t y = 0 ; y < (M->yl * 9); y++ ) {
            
           printf("\"");
            
        }
        printf(" ");
    }
    else {

        printf(" ");
        for ( size_t y = 0 ; y < (M->yl * 9) ; y++ ) {
            
            printf(" ");
        }
        printf(" ");

    }
}

static size_t max(unsigned int* rows, short nb_rows) {

    size_t max = rows[0];

    for ( short i = 1 ; i < nb_rows ; ++i ) {

        if (max < rows[i]) {

            max = rows[i];
        }
    }

    return max;
}

void NnPrettyPrint(NeuralNet* NN) {

    printTitle("INPUT", L0->yl);
    printTitle("W0to1", W0to1->yl);
    printTitle("B1___", B1->yl);
    printTitle("L1___", L1->yl);
    printTitle("W1to2", W1to2->yl);
    printTitle("B2___", B2->yl);
    printTitle("OUT__", L2->yl);
    printTitle("E_OUT", OUT->yl);
    printf("\n");

    unsigned int rows[8] = { L0->xl, W0to1->xl,
                             B1->xl, L1->xl, W1to2->xl, 
                             B2->xl, L2->xl, OUT->xl };

    for ( size_t i = 0 ; i < max(rows, 8) + 1 ; ++i ) {
        
        printRow(L0, i);
        printRow(W0to1, i);
        printRow(B1, i);
        printRow(L1, i);
        printRow(W1to2, i);
        printRow(B2, i);
        printRow(L2, i);
        printRow(OUT, i);
        printf("\n");
    }

    
}

static float absFloat(float f) {

    if (f < 0) {

        f = -f;
    }

    return f;
}

float NnGetError(NeuralNet* NN) {

    Mat* Errors = mSub(NN->out, NN->l2);
    
    float sum = 0.0;

    for ( size_t x = 0 ; x < Errors->xl ; ++x ) {

        float a = mGet(Errors, x, 0);
        a = absFloat(a);
        sum += a;
    }

    float divide = Errors->xl;
    mFree(Errors);
    return sum / divide;

}