#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "list.h"
#include "Bitmap.h"

#ifndef ONLYONCE_SIZE
#define ONLYONCE_SIZE

Bitmap* AdjustChar(List l, Bitmap *b);

Bitmap* sizeUP(Bitmap* b);

Bitmap* sizeDO(Bitmap* b);

Bitmap* fromCutToNN(List l, Bitmap* b);

void lettersPrettyPrint(List *l, Bitmap *b);
#endif
