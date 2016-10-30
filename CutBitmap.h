#include "list.h"
#include "Bitmap.h"

#ifndef ONLYONCE_CUTBITMAP
#define ONLYONCE_CUTBITMAP

List* cutblockY(int* tab, Bitmap *b, int* policeSize);

List* cutblockX(int* tab, Bitmap *b, int* policeSize);

List* Cutlines(int* tab,Bitmap* b);

List* Cutchars(int* tab,Bitmap* b, int PoliceSize);

List* CutAll(Bitmap* b);

//struct list *CutAll(Bitmap *b);
#endif
