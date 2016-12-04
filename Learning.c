# include <stdlib.h>
# include <err.h>
# include <assert.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "NeuralNet.h"
# include "Matrix.h"
# include "save.h"
# include "loadLearningImage.h"

#define NB_OF_CHAR 94
#define NB_NEURONS_L1 3

static void lrnSaveNeuralNet(NeuralNet* NN, char* path);

static void lrnLoadNeuralNet(NeuralNet* NN, char* path);

static void lrnLoadTrainingMatrix(Mat* Input, Mat* Output, char* path);

void lrnStartLearning(char* train_path, char* nn_path, int loops) {

    warnx("####################");
    warnx("# LEARNING STARTED #");
    warnx("####################");

    // Init Input/Output
    Mat* Input = mNewFill(NB_OF_CHAR, 24*24, 0.0);
    Mat* Output = mNewFill(NB_OF_CHAR, NB_OF_CHAR, 0.0);

    lrnLoadTrainingMatrix(Input, Output, train_path);
    
    // Init NeuralNet
    NeuralNet* NN = NnInit(Input, Output, NB_NEURONS_L1, NB_OF_CHAR);

    mFree(Input);
    mFree(Output);

    // Load weights and bias
    lrnLoadNeuralNet(NN, nn_path);

    warnx("Let's start the leraning !");

    warnx("Begin error : %f", NnGetError(NN));

    // Begin learning
    float prev = 0.0;
    float next = 0.0;
    for ( int l = 0 ; l < loops ; ++l ) {

        // Learn
        NnLearn(NN);

        if (l % 1000 == 0) {
            
            next = NnGetError(NN);
            float per = ((float)l / (float)loops) * 100.0;
            warnx("%5.1f percent > Error : %50.50f > Delta : %50.50f", per, next, next-prev);
            prev = next;
            lrnSaveNeuralNet(NN, nn_path);            
        }
    }

    lrnSaveNeuralNet(NN, nn_path);
    NnBigPrint(NN);
    NnFree(NN);
}

void lrnInitNeuralNet(char* train_path, char* nn_path) {

    Mat* Input = mNewFill(NB_OF_CHAR, 24*24, 0.0);
    Mat* Output = mNewFill(NB_OF_CHAR, NB_OF_CHAR, 0.0);

    warnx("INIT : loading training matrix");
    lrnLoadTrainingMatrix(Input, Output, train_path);

    NeuralNet* NN = NnInit(Input, Output, NB_NEURONS_L1, NB_OF_CHAR);

    mPrintDim(NN->w0to1, "Debug : lrnInitNN : W0TO1");
    mPrintDim(NN->w1to2, "Debug : lrnInitNN : W1TO2");
    lrnSaveNeuralNet(NN, nn_path);

    NnBigPrint(NN);
}

char* getCharFromMat(Mat* I) {

    char* result = malloc(sizeof(char) * I->xl);

    Mat* P_Out = mNewFill(I->xl, 94, 0.0);

    lrnLoadTrainingMatrix(I, P_Out, "ascii6.bmp");

    NeuralNet* NN = NnInit(I, P_Out, NB_NEURONS_L1, 94);

    NnLoad(NN->w0to1, NN->w1to2, NN->b1, NN->b2, "save.txt");

    NnFeedForward(NN);

    Mat* R = NN->l2;

    mPrintCompact(R, "R");
    for ( size_t x = 0 ; x < R->xl ; ++x ) {
        
        size_t i = 0;

        while (i < R->yl && mGet(R, x, i) < 0.7) {

            i++;
        }

        if (i >= R->yl || i == 1) {

            result[x] = ' ';
        }
        else if (i == 0) {

            result[x] = '!';
        }
        else {

            result[x] = 33 + i;
        }

        warnx("getCharFromMat : %ld = %d", i, result[i]);
    }

    NnFree(NN);
    mFree(P_Out);
    
    return result;
}

// #########################################################

static void lrnSaveNeuralNet(NeuralNet* NN, char* path) {

    NnSave(NN->w0to1, NN->w1to2, NN->b1, NN->b2, path);
}

static void lrnLoadNeuralNet(NeuralNet* NN, char* path) {

    NnLoad(NN->w0to1, NN->w1to2, NN->b1, NN->b2, path);
}

// ####################
// LOAD IMAGE FOR THE LUCAS BREAKDOWN
// ####################

/* 
static void init_sdl(void) {

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {

        errx(1, "Could not init SDL: %s.\n", SDL_GetError());
    }
}

static SDL_Surface* load_image(char* path) {

    SDL_Surface* img = IMG_Load(path);

    if (!img) {

        errx(3, "cant load %s: %s", path, IMG_GetError());
    }

    return img;
}

static inline Uint8* pixelref(SDL_Surface* surface, unsigned x, unsigned y) {

    int bpp = surface->format->BytesPerPixel;
    return (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
}

static Uint32 getpixelSurface(SDL_Surface *surface, unsigned x, unsigned y) {

    Uint8 *p = pixelref(surface, x, y);
    switch (surface->format->BytesPerPixel) {

        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
    }

    return 0;
}

static loadToMatrix(Mat* M, char *path, unsigned int line) {

    init_sdl();
    SDL_Surface *surface = load_image(path);
    Uint8 r, g, b;
    size_t i = 0;
    for ( int w = 0 ; w < surface->w ; ++w ) {

        for ( int h = 0 ; h < surface->h ; ++h ) {
            
            Uint32 pixel = getpixelSurface(surface, w, h);
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);
            float lum = (0.3 * r + 0.59 * g + 0.11 * b);

            if (lum > 120) 
                mSet(M, line, i, 1.0);
            else 
                mSet(M, line, i, 0.0);

            ++i;
        }
    }
}

static void lrnLoadBigTM(Mat* Input, Mat* Output) {

    init_sdl(); 
         

}
*/


  
static void lrnLoadTrainingMatrix(Mat* Input, Mat* Output, char* path) {

    warnx("Loading Training Matrix...");

    Mat* I = learningNN(path);
    Mat* O = learningNNOutput();

    mCopyAinB(I, Input);
    mCopyAinB(O, Output);

    mFree(I);
    mFree(O);

    warnx("Training Matrix Loaded.");
}
