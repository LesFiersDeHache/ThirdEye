#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "list.h"
#include "Bitmap.h"
#include "listB.h"


#ifndef ONLYONCE_SIZE
#define ONLYONCE_SIZE

Bitmap* AdjustChar(List l, Bitmap *b);

Bitmap* sizeUP(Bitmap* b);

Bitmap* sizeDO(Bitmap* b);

Bitmap* fromCutToNN(List l, Bitmap* b);

void lettersPrettyPrint(List *l, Bitmap *b);

struct listB* sendList(List *l, Bitmap* b);

void showResize(Bitmap* b);
#endif
