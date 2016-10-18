#include "Bitmap.h"
#include  "list.h"

#ifndef ONLYONCE_CUTBITMAP
#define ONLYONCE_CUTBITMAP

struct list* cutblockY(Bitmap bmp);

struct list* cutblockX(Bitmap bmp);

struct list* CutLines(Bitmap bmp);
#endif