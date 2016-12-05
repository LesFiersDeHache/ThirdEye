#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "list.h"
#include "Bitmap.h"
#include "listB.h"


#ifndef ONLYONCE_SIZE
#define ONLYONCE_SIZE

Bitmap* AdjustChar(List l, Bitmap *b, int arg);

Bitmap* sizeUP(Bitmap* b, int arg);

Bitmap* sizeDO(Bitmap* b, int arg);

Bitmap* fromCutToNN(List l, Bitmap* b, int arg);

void lettersPrettyPrint(List *l, Bitmap *b);

struct listB* sendList(List *l, Bitmap* b);

void showResize(Bitmap* b);
#endif
