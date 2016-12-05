#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <err.h>
#include "Bitmap.h"
#include "listB.h"

#ifndef ONLYONCE_loadLearningImage
#define ONLYONCE_loadLearningImage

Mat* learningNNOutput();

Mat* learningNN(char *path);

Mat* bitmapToMat(Bitmap *b);

Mat* listbmpToMat(struct listB *res);

#endif
