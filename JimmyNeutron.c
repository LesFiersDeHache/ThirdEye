#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <err.h>

#include "NeuralNet.h"
#include "Matrix.h"
#include "save.h"
#include "Bitmap.h"
#include "list.h"
#include "CutBitmap.h"
#include "SDLstuff.h"
#include "listB.h"
#include "resize.h"
#include "loadLearningImage.h"

// ############ INIT ##################//



static void initLearningMatrix(Mat* Input, Mat* Output) {

    Mat* _In = learningNN("ascii5.jpg");
    Mat* _Out = learningNNOutput();

    mPrintDim(_Out, "Out");
    mPrintDim(Output, "Output");
    mCopyAinB(_In, Input);
    mCopyAinB(_Out, Output); // NOT SAME DIM !!!

    mFree(_In);
    mFree(_Out);
}

NeuralNet* JnInitJn() {

    Mat* Input = mNewFill(94, 24*24, 0.0);
    Mat* Output = mNewFill(94, 94, 0.0);

    initLearningMatrix(Input, Output);

    NeuralNet* JN = NnInit(Input, Output, 30, 94);

    mFree(Input);
    mFree(Output);

    return JN;
}

// ############ SAVE/LOAD #############//

void JnLoadWeights(NeuralNet* JN) {

    NnLoad(JN->w0to1, JN->w1to2, JN->b1, JN->b2, "Jimmy.txt");
}

void JnSaveWeights(NeuralNet* JN) {

    NnSave(JN->w0to1, JN->w1to2, JN->b1, JN->b2, "Jimmy.txt");
}

// ############ LEARNING ##############//

void JnLearnOneTime(NeuralNet* JN) {

    NnLearn(JN);
}

void JnLearn(NeuralNet* JN, size_t loop) {

    
    for (size_t l = 0 ; l < loop ; ++l ) {

        JnLearnOneTime(JN);

        if (l % 100 == 0) {

            warnx("Round : %ld -> Error : %f", l, NnGetError(JN));
        }
    }

    warnx("#### OVER ####");
}

// ######### CALC ERROR ############ //


