#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <assert.h>
#include "NeuralNetwork.h"
#include "FeedForward.h"
#include "BackFeed.h"
#include "Sigmoid.h"
#include <time.h>
#include "list.h"
#include "CutBitmap.h"
#include "SDLstuff.h"
#include "Bitmap.h"
#include "Matrix.h"

#define NB_OF_LOOPS 10000 
#define MODE 1
#define PRINT 0

#define MULT 2.0
#define ADD -1.0
Mat* initInputDataSet(float a1, float a2, float b1, float b2, 
                      float c1, float c2, float d1, float d2);
                      
Mat* initOutputDataSet(float a, float b,
                       float c, float d);

int main() {
    
    // #### NEURAL NETWORK #### //

    //INIT
    
    //Initialize DataSets for Training
    Mat* In_Dt_Set = initInputDataSet( 0.0,0.0,1.0,0.0,0.0,1.0,1.0,1.0 );

    Mat* Ou_Dt_Set = initOutputDataSet( 0.0, 1.0, 1.0, 0.0 );
    
    //Set weights
    Mat* Weight_0_To_1 = newMatRandom(3, 4, MULT, ADD); //CAN BE A MISTAKE

    Mat* Weight_1_To_2 = newMatRandom(4, 1, MULT, ADD); //CAN BE A MISTAKE

    for (unsigned int loop = 0 ; loop < NB_OF_LOOPS ; ++loop) {

        // L0 = X
        Mat* Layer_0 = ope_Mcopy(In_Dt_Set);
        // L1 = sigmoid(L0 dot wg0)
        Mat* Layer_1 = ope_apply_sigmoid(ope_VdotM(Layer_0, Weight_0_To_1));
        // L2 = sigmoid(L1 dot wg1)
        Mat* Layer_2 = ope_apply_sigmoid(ope_VdotM(Layer_0, Weight_0_To_1));
        // L2_error = Y - L2
        Mat* L_2_Err = ope_MpM(Ou_Dt_Set, ope_MpR(Layer_2, -1.0));
        // L2_delta = L2_error * sigmoid'(L2)
        Mat* L_2_Dlt = ope_MxM(L_2_Err, ope_apply_deriv_sigmoid(Layer_2));
        // L1_error = L2_delta dot wg1
        Mat* L_1_Err = ope_VdotM(L_2_Dlt, Weight_1_To_2);
        // L1_delta = L1_error * sigmoid'(L1)
        Mat* L_1_Dlt = ope_MxM(L_1_Err, ope_apply_deriv_sigmoid(Layer_1));
        // wg0 += L1.T dot L2_delta
        Weight_0_To_1 = ope_MpM(Weight_0_To_1, 
                                ope_VdotV(ope_Mt(Layer_1), 
                                L_2_Dlt));
        // wg1 += L0.T dot L1_delta
        Weight_1_To_2 = ope_MpM(Weight_1_To_2,
                                ope_VdotV(ope_Mt(Layer_0), 
                                L_1_Dlt));
    }
}

Mat* initInputDataSet(float a1, float a2, float b1, float b2,
                      float c1, float c2, float d1, float d2) {

    Mat* mat_sol = newMat(4, 2, 0.0);

    mat_sol->tab[0] = a1;
    mat_sol->tab[1] = a2;
    mat_sol->tab[2] = b1;
    mat_sol->tab[3] = b2;
    mat_sol->tab[4] = c1;
    mat_sol->tab[5] = c2;
    mat_sol->tab[6] = d1;
    mat_sol->tab[7] = d2;

    return mat_sol;
}

Mat* initOutputDataSet(float a, float b, float c, float d) {
    
    Mat* mat_sol;

    mat_sol->tab[0] = a;
    mat_sol->tab[1] = b;
    mat_sol->tab[2] = c;
    mat_sol->tab[3] = d;

    return mat_sol;
}
